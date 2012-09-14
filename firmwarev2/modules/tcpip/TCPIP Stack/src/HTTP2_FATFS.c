#ifndef __HTTP2_C
#define __HTTP2_C

#include "TCPIP Stack/TCPIP.h"

#if defined(STACK_USE_HTTP2_SERVER)

/****************************************************************************
  Section:
  String Constants
  ***************************************************************************/
  ROM BYTE HTTP_CRLF[] = "\r\n"; // New line sequence
    
/****************************************************************************
  Section:
  File and Content Type Settings
  ***************************************************************************/
  // File type extensions corresponding to HTTP_FILE_TYPE
  ROM char * ROM httpFileExtensions[HTTP_UNKNOWN+1] =
  {
      "txt",          // HTTP_TXT
      "htm",          // HTTP_HTM
      "html",         // HTTP_HTML
      "cgi",          // HTTP_CGI
      "xml",          // HTTP_XML
      "css",          // HTTP_CSS
      "gif",          // HTTP_GIF
      "png",          // HTTP_PNG
      "jpg",          // HTTP_JPG
      "cla",          // HTTP_JAVA
      "wav",          // HTTP_WAV
      "js",           // HTTP_JS
      "json",         // HTTP_JSON
    "\0\0\0"    // HTTP_UNKNOWN
  };
  
  // Content-type strings corresponding to HTTP_FILE_TYPE
  ROM char * ROM httpContentTypes[HTTP_UNKNOWN+1] =
  {
      "text/plain",            // HTTP_TXT
      "text/html",             // HTTP_HTM
      "text/html",             // HTTP_HTML
      "text/html",             // HTTP_CGI
      "text/xml",              // HTTP_XML
      "text/css",              // HTTP_CSS
      "image/gif",             // HTTP_GIF
      "image/png",             // HTTP_PNG
      "image/jpeg",            // HTTP_JPG
      "application/java-vm",   // HTTP_JAVA
      "audio/x-wave",          // HTTP_WAV
      "text/javascript",       // HTTP_JS
      "application/json",      // HTTP_JSON
    ""             // HTTP_UNKNOWN
  };

/****************************************************************************
  Section:
  Header Parsing Configuration
  ***************************************************************************/
  
  // Header strings for which we'd like to parse
  ROM char * ROM HTTPRequestHeaders[] =
  {
    "Cookie:",
    "Authorization:",
    "Content-Length:"
  };

  // Header strings for which we'd like to parse
  ROM char * ROM HTTPSupportedHeaders[] =
  {
    "Cookie:",
    "Authorization: ",
    "Content-Length: ",
    "Content-Type: ",
    "Connection: "
  };

  /****************************************************************************
  Section:
  Commands and Server Responses
  ***************************************************************************/

  // Initial response strings (Corresponding to HTTP_STATUS)
  ROM char * ROM HTTPResponseHeaders[] =
  {
    "HTTP/1.1 200 OK\r\nConnection: close\r\n",
    "HTTP/1.1 400 Bad Request\r\nConnection: close\r\n\r\n400 Bad Request: can't handle Content-Length\r\n",
    "HTTP/1.1 401 Unauthorized\r\nWWW-Authenticate: Basic realm=\"Protected\"\r\nConnection: close\r\n\r\n401 Unauthorized: Password required\r\n",
    "HTTP/1.1 404 Not found\r\nConnection: close\r\n\r\n404: File not found\r\n",
    "HTTP/1.1 414 Request-URI Too Long\r\nConnection: close\r\n\r\n414 Request-URI Too Long: Buffer overflow detected\r\n",
    "HTTP/1.1 500 Internal Server Error\r\nConnection: close\r\n\r\n500 Internal Server Error: Expected data not present\r\n",
    "HTTP/1.1 501 Not Implemented\r\nConnection: close\r\n\r\n501 Not Implemented: Only GET and POST supported\r\n",
    "HTTP/1.1 302 Found\r\nConnection: close\r\nLocation: ",
    "HTTP/1.1 403 Forbidden\r\nConnection: close\r\n\r\n403 Forbidden: SSL Required - use HTTPS\r\n"
  };
  
  // Set to length of longest string above
  #define HTTP_MAX_HEADER_LEN   (15u)

#endif

/****************************************************************************
  Section:
  HTTP Connection State Global Variables
  ***************************************************************************/
  HTTP_SERVER_CONNECTION httpConnections[MAX_HTTP_CONNECTIONS];
  BYTE activeConnectionID;

/****************************************************************************
Section:
Function Prototypes
***************************************************************************/
static void HTTPHeaderParseLookup(BYTE i);
#if defined(HTTP_USE_COOKIES)
static void HTTPHeaderParseCookie(void);
#endif
#if defined(HTTP_USE_AUTHENTICATION)
static void HTTPHeaderParseAuthorization(void);
#endif
#if defined(HTTP_USE_POST)
static void HTTPHeaderParseContentLength(void);
static HTTP_READ_STATUS HTTPReadTo(BYTE delim, BYTE* buf, WORD len);
#endif

static void HTTPProcess(void);
static BOOL HTTPSendFile(void);
static void HTTPLoadConn(BYTE hHTTP);

// Not used right now but we'll leave it in case we decide to use it later
//#define mMIN(a, b)  ((a<b)?a:b)

/*****************************************************************************
  Function:
  void HTTPInit(void)

  Summary:
  Initializes the HTTP server module.

  Description:
  Sets all HTTP sockets to the listening state, and initializes the
  state machine and file handles for each connection.  If SSL is
  enabled, opens a socket on that port as well.

  Precondition:
  TCP must already be initialized.

  Parameters:
  None

  Returns:
    None
    
  Remarks:
  This function is called only once during lifetime of the application.
  ***************************************************************************/
void HTTPInit(void)
{

  for(activeConnectionID = 0; activeConnectionID < MAX_HTTP_CONNECTIONS; activeConnectionID++)
  {
    activeConnectionState = SM_HTTP_IDLE;
    activeSocket = TCPOpen(0, TCP_OPEN_SERVER, HTTP_PORT, TCP_PURPOSE_HTTP_SERVER);
    #if defined(STACK_USE_SSL_SERVER)
    TCPAddSSLListener(activeSocket, HTTPS_PORT);
    #endif
  }

  activeConnectionID = 0;  
}


/*****************************************************************************
  Function:
  void HTTPServer(void)

  Summary:
  Performs periodic tasks for the HTTP2 module.

  Description:
  Browses through each open connection and attempts to process any
  pending operations.

  Precondition:
  HTTPInit() must already be called.

  Parameters:
  None

  Returns:
    None
    
  Remarks:
  This function acts as a task (similar to one in an RTOS).  It
  performs its task in a co-operative manner, and the main application
  must call this function repeatedly to ensure that all open or new
  connections are served in a timely fashion.
  ***************************************************************************/
void HTTPServer(void)
{
  BYTE conn;

  for(conn = 0; conn < MAX_HTTP_CONNECTIONS; conn++)
  {
    if(httpConnections[conn].socket == INVALID_SOCKET)
      continue;
    
    // If a socket is disconnected at any time 
    // forget about it and return to idle state.
    // Must do this here, otherwise we will wait until a new
    // connection arrives, which causes problems with Linux and with SSL
    if(TCPWasReset(httpConnections[conn].socket))
    {
      HTTPLoadConn(conn);
      activeConnectionState = SM_HTTP_IDLE;

      // Make sure any opened files are closed
      if(activeConnection.file != NULL)
      {
        FATFS_fclose(activeConnection.file);
        activeConnection.file = NULL;
      }

      // Adjust FIFO sizes to half and half.  Default state must remain
      // here so that SSL handshakes, if required, can proceed
      TCPAdjustFIFOSize(activeSocket, 1, 0, TCP_ADJUST_PRESERVE_RX);
    }
    
    // Determine if this connection is eligible for processing
    if(httpConnections[conn].state != SM_HTTP_IDLE || TCPIsGetReady(httpConnections[conn].socket))
    {
      HTTPLoadConn(conn);
      HTTPProcess();
    }
  }
}

/*****************************************************************************
  Function:
  static void HTTPLoadConn(BYTE hHTTP)

  Summary:
  Switches the currently loaded connection for the HTTP2 module.

  Description:
  Saves the currently loaded HTTP connection back to Ethernet buffer
  RAM, then loads the selected connection into curHTTP in local RAM
  for processing.

  Precondition:
  None

  Parameters:
  hHTTP - the connection ID to load

  Returns:
    None
  ***************************************************************************/
static void HTTPLoadConn(BYTE hHTTP)
{
  WORD oldPtr;
    
  // Return if already loaded
  if(hHTTP == activeConnectionID)
    return;
    
  // Before we switch let's flush the existing connection
  TCPFlush(activeSocket);
  activeConnectionID = hHTTP;
      
}

/*****************************************************************************
  Function:
  static void HTTPProcess(void)

  Description:
  Performs any pending operations for the currently loaded HTTP connection.

  Precondition:
  HTTPInit() and HTTPLoadConn() have been called.

  Parameters:
  None

  Returns:
    None
  ***************************************************************************/
static void HTTPProcess(void)
{
  WORD lenA, lenB;
  BYTE c, i;
  BOOL isDone;
  BYTE *ext;
  BYTE buffer[HTTP_MAX_HEADER_LEN+1];
  BYTE tempflag=FALSE;

  do
  {
    isDone = TRUE;

    switch(activeConnectionState)
    {

      case SM_HTTP_IDLE:

        // Check how much data is waiting
        lenA = TCPIsGetReady(activeSocket);

        // A new connection has been made so let's initialize the 
        // connection object to a known state.
        if(lenA)
        {

          ServerConnection_Initialize(&activeConnection);
          
          activeConnectionState = SM_HTTP_PARSE_REQUEST;

          // Adjust the TCP FIFOs for optimal reception of 
          // the next HTTP request from the browser
          TCPAdjustFIFOSize(activeSocket, 1, 0, TCP_ADJUST_PRESERVE_RX | TCP_ADJUST_GIVE_REST_TO_RX);
        }
        else
          // Don't break for new connections.  There may be 
          // an entire request in the buffer already.
          break;

      case SM_HTTP_PARSE_REQUEST:

        // Verify the entire first line is in the FIFO
        if(TCPFind(activeSocket, '\n', 0, FALSE) == 0xffff)
        {// First line isn't here yet
          if(TCPGetRxFIFOFree(activeSocket) == 0u)
          {// If the FIFO is full, we overflowed
            activeResponse.status = HTTP_OVERFLOW;
            activeConnectionState = SM_HTTP_HANDLE_ERROR;
            isDone = FALSE;
          }
          if((LONG)(TickGet() - activeConnection.wdTimer) > (LONG)0)
          {// A timeout has occurred
            TCPDisconnect(activeSocket);
            activeConnectionState = SM_HTTP_DISCONNECT;
            isDone = FALSE;
          }
          break;
        }

        // Reset the watchdog timer
        activeConnection.wdTimer = TickGet() + HTTP_TIMEOUT*TICK_SECOND;

        // Determine the request method
        lenA = TCPFind(activeSocket, ' ', 0, FALSE);
        if(lenA > 6u) // 6 to accomodate DELETE
          lenA = 6;

        TCPGetArray(activeSocket, activeConnection.data, lenA+1);

        if(memcmppgm2ram(activeConnection.data, (ROM void*)"GET", 3) == 0)
          activeRequest.method = HTTP_GET;
        #if defined(HTTP_USE_POST)
        else if ( memcmppgm2ram(activeConnection.data, (ROM void*)"POST", 4) == 0)
          activeRequest.method = HTTP_POST;
        #endif
        else
        {// Unrecognized method, so return not implemented
          activeResponse.status = HTTP_NOT_IMPLEMENTED;
          activeConnectionState = SM_HTTP_HANDLE_ERROR;
          isDone = FALSE;
          break;
        }

        // Find end of uri
        lenA = TCPFind(activeSocket, ' ', 0, FALSE);
        
        // If the uri is too long, then reject the request
        if(lenA > HTTP_MAX_DATA_LEN - HTTP_DEFAULT_LEN - 1)
        {
          activeResponse.status = HTTP_OVERFLOW;
          activeConnectionState = SM_HTTP_HANDLE_ERROR;
          isDone = FALSE;
          break;
        }

        // Read in the request uri with query string
        lenB = TCPGetArray(activeSocket, activeConnection.data, lenA);
        activeConnection.data[lenB] = '\0';
        strcpy(activeRequest.url, activeConnection.data);


        // Clear the rest of the line
        lenA = TCPFind(activeSocket, '\n', 0, FALSE);
        TCPGetArray(activeSocket, NULL, lenA + 1);

        // Move to parsing the headers
        activeConnectionState = SM_HTTP_PARSE_HEADERS;
        
        // No break, continue to parsing headers

    case SM_HTTP_PARSE_HEADERS:

      // Loop over all the headers
      while(1)
      {
        // Make sure entire line is in the FIFO
        lenA = TCPFind(activeSocket, '\n', 0, FALSE);
        if(lenA == 0xffff)
        {// If not, make sure we can receive more data
          if(TCPGetRxFIFOFree(activeSocket) == 0u)
          {// Overflow
            activeResponse.status = HTTP_OVERFLOW;
            activeConnectionState = SM_HTTP_HANDLE_ERROR;
            isDone = FALSE;
          }
          if((LONG)(TickGet() - activeConnection.wdTimer) > (LONG)0)
          {// A timeout has occured
            TCPDisconnect(activeSocket);
            activeConnectionState = SM_HTTP_DISCONNECT;
            isDone = FALSE;
          }
          break;
        }
        
        // Reset the watchdog timer
        activeConnection.wdTimer = TickGet() + HTTP_TIMEOUT*TICK_SECOND;
        
        // If a CRLF is immediate, then headers are done
        if(lenA == 1u)
        {// Remove the CRLF and move to next state
          TCPGetArray(activeSocket, NULL, 2);
          activeConnectionState = SM_HTTP_AUTHENTICATE;
          isDone = FALSE;
          break;
        }
  
        // Find the header name, and use isDone as a flag to indicate a match
        lenB = TCPFindEx(activeSocket, ':', 0, lenA, FALSE) + 2;
        isDone = FALSE;
  
        // If name is too long or this line isn't a header, ignore it
        if(lenB > sizeof(buffer))
        {
          TCPGetArray(activeSocket, NULL, lenA+1);
          continue;
        }
        
        // Read in the header name
        TCPGetArray(activeSocket, buffer, lenB);
        buffer[lenB-1] = '\0';
        lenA -= lenB;
    
        // Compare header read to ones we're interested in
        for(i = 0; i < sizeof(HTTPRequestHeaders)/sizeof(HTTPRequestHeaders[0]); i++)
        {
          if(strcmppgm2ram((char*)buffer, (ROM char *)"Content-Length") == 0)
          {// Parse the header and stop the loop
            HTTPHeaderParseContentLength();
            isDone = TRUE;
            break;
          }
        }
        
        // Clear the rest of the line, and call the loop again
        if(isDone)
        {// We already know how much to remove unless a header was found
          lenA = TCPFind(activeSocket, '\n', 0, FALSE);
        }
        TCPGetArray(activeSocket, NULL, lenA+1);
      }
      
      break;

    case SM_HTTP_AUTHENTICATE:
    
      // Not supporting HTTP Authentication for now
      // Will implement a simple forms-based auth if
      // necessary
      
      // Move on to correct state
      if(activeRequest.method == HTTP_GET)
        activeConnectionState = SM_HTTP_PROCESS_GET;
      else
        activeConnectionState = SM_HTTP_PROCESS_POST;

      isDone = FALSE;
      break;

    case SM_HTTP_PROCESS_GET:

      // Run the application callback HTTPExecuteGet()
      if(HttpServeResponse() == HTTP_IO_WAITING)
      {
        // If waiting for asynchronous process, return to main app
        break;
      }

      activeConnectionState = SM_HTTP_DISCONNECT;
      break;

    case SM_HTTP_PROCESS_POST:

      #if defined(HTTP_USE_POST)
      
      // See if we have any new data
      if(TCPIsGetReady(activeSocket) == activeConnection.bytesAvailable)
      {
        if((LONG)(TickGet() - activeConnection.wdTimer) > (LONG)0)
        {// If a timeout has occured, disconnect
          TCPDisconnect(activeSocket);
          activeConnectionState = SM_HTTP_DISCONNECT;
          isDone = FALSE;
          break;
        }
      }
      
      if(activeRequest.method == HTTP_POST)
      {
        // Run the application callback HTTPExecutePost()
        c = HttpServeResponse();
        
        // If waiting for asynchronous process, return to main app
        if(c == (BYTE)HTTP_IO_WAITING)
        {
          // return to main app and make sure we don't get stuck by the watchdog
          activeConnection.bytesAvailable = TCPIsGetReady(activeSocket) - 1;
          break;
        }
        else if(c == (BYTE)HTTP_IO_NEED_DATA)
        {
          // If waiting for more data
          activeConnection.bytesAvailable = TCPIsGetReady(activeSocket);
          activeConnection.wdTimer = TickGet() + HTTP_TIMEOUT*TICK_SECOND;
          
          // If more is expected and space is available, return to main app
          if(activeRequest.contentLength > activeConnection.bytesAvailable && TCPGetRxFIFOFree(activeSocket) != 0u)
            break;
          
          // Handle cases where application ran out of data or buffer space
          activeResponse.status = HTTP_INTERNAL_SERVER_ERROR;
          activeConnectionState = SM_HTTP_HANDLE_ERROR;
          isDone = FALSE;
          break;  
        }
      }
      #endif

      // We're done with POST
      activeConnectionState = SM_HTTP_DISCONNECT;
      break;

    case SM_HTTP_HANDLE_ERROR:

      TCPAdjustFIFOSize(activeSocket, 1, 0, TCP_ADJUST_GIVE_REST_TO_TX);
        
      // Send headers
      TCPPutROMString(activeSocket, (ROM BYTE*)HTTPResponseHeaders[activeResponse.status]);

      activeConnectionState = SM_HTTP_DISCONNECT;
      break;

    case SM_HTTP_DISCONNECT:
      // Make sure any opened files are closed
      if(activeConnection.file != NULL)
      {
        FATFS_fclose(activeConnection.file);
        activeConnection.file = NULL;
      }

      TCPDisconnect(activeSocket);
      activeConnectionState = SM_HTTP_IDLE;
      break;
    }
  } while(!isDone);

}

/*****************************************************************************
  Function:
  static void HTTPHeaderParseContentLength(void)

  Summary:
  Parses the "Content-Length:" header for a request.

  Description:
  Parses the "Content-Length:" header to determine how many bytes of
  POST data to expect after the request.  This value is stored in 
  curHTTP.byteCount.

  Precondition:
  None

  Parameters:
  None

  Returns:
  None

  Remarks:
  This function is ony available when HTTP_USE_POST is defined.
  ***************************************************************************/
#if defined(HTTP_USE_POST)
static void HTTPHeaderParseContentLength(void)
{
  WORD len;
  BYTE buf[10];

  // Read up to the CRLF (max 9 bytes or ~1GB)
  len = TCPFindROMArray(activeSocket, HTTP_CRLF, HTTP_CRLF_LEN, 0, FALSE);
  if(len >= sizeof(buf))
  {
    activeResponse.status = HTTP_BAD_REQUEST;
    activeRequest.contentLength = 0;
    return;
  } 
  len = TCPGetArray(activeSocket, buf, len);
  buf[len] = '\0';
  
  activeRequest.contentLength = atol((char*)buf);
}
#endif

#endif