/*************************************************************************
 *
 *  HyperText Transfer Protocol (HTTP) Server With MDD File System Support
 *  Module for Microchip TCP/IP Stack
 *   -Serves dynamic pages to web browsers such as Microsoft Internet 
 *    Explorer, Mozilla Firefox, etc.
 *   -Reference: RFC 2616
 *
 **************************************************************************
 * FileName:        HTTP2.c
 * Dependencies:    TCP, MPFS2, Tick, CustomHTTPApp.c callbacks
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *          Microchip C30 v3.12 or higher
 *          Microchip C18 v3.30 or higher
 *          HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *    ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *    used in conjunction with a Microchip ethernet controller for
 *    the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Amit Shirbhate  7/18/09     Modified original for MDD FAT support.(Beta Release)
 ***************************************************************************************/

#define __HTTP2_C

#include "TCPIP Stack/TCPIP.h"

#if defined(STACK_USE_HTTP2_SERVER)

//#include "HTTPPrint.h"

/****************************************************************************
  Section:
  String Constants
  ***************************************************************************/
  ROM BYTE HTTP_CRLF[] = "\r\n"; // New line sequence
  //#define HTTP_CRLF_LEN 2       // Length of above string
    
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

/*#ifdef STACK_USE_MDD 
static WORD nameHash=0;
BYTE incDataBuffer[64];
BYTE sendDataBuffer[64];
BYTE CurWorkDirChangedToMddRootPath=FALSE;
BYTE EndOfCallBackFileFlag=FALSE;
BYTE dirlen;
BYTE * directoryPtr=NULL; 
extern volatile BOOL MemInterfaceAttached;  
*/

//Name of file having log of "Files with Dynamic Variables" Sorted in Ascending order using hash name 
//const char filename[]="FileRcrd.bin"; //File Record
//const char dynVarRcrdFileName[]="DynRcrd.bin";//Dynamic variable Record
//FILE_HANDLE FileRcrdPtr=NULL;
//static FILE_HANDLE DynVarRcrdFilePtr=NULL;

#endif

/****************************************************************************
  Section:
  HTTP Connection State Global Variables
  ***************************************************************************/
  #if defined(__18CXX) && !defined(HI_TECH_C) 
    #pragma udata HTTP_CONNECTION_STATES
  #endif
  //HTTP_CONN curHTTP;              // Current HTTP connection state
  //HTTP_SERVER_REQUEST currentRequest;
  //HTTP_STUB httpConnections[MAX_HTTP_CONNECTIONS];  // HTTP stubs with state machine and socket
  //BYTE curHTTPID;               // ID of the currently loaded HTTP_CONN
  HTTP_SERVER_CONNECTION httpConnections[MAX_HTTP_CONNECTIONS];
  //HTTP_SERVER_CONNECTION activeConnection;
  BYTE activeConnectionID;

  #if defined(__18CXX) && !defined(HI_TECH_C) 
    #pragma udata
  #endif

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
//static FILE_HANDLE FileOpenIndex(FILE_HANDLE hFile, BYTE * fileName);
//static WORD FileGetFlags(FILE_HANDLE hFile);


#define mMIN(a, b)  ((a<b)?a:b)
//#define smHTTP    httpConnections[curHTTPID].sm     // Access the current state machine
// #define activeConnection = (httpConnections[activeConnectionID])
// #define activeConnectionState  (httpConnections[activeConnectionID].state)
// #define activeRequest (httpConnections[activeConnectionID].request)
// #define activeResponse  (httpConnections[activeConnectionID].response)

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
  This function is called only one during lifetime of the application.
  ***************************************************************************/
void HTTPInit(void)
{
  PTR_BASE oldPtr;

  // Make sure the file handles are invalidated
  //curHTTP.file = INVALID_FILE_HANDLE;
  //curHTTP.offsets = INVALID_FILE_HANDLE;
  //curHTTP.file = NULL;
    
  for(activeConnectionID = 0; activeConnectionID < MAX_HTTP_CONNECTIONS; activeConnectionID++)
  {
    activeConnectionState = SM_HTTP_IDLE;
    activeSocket = TCPOpen(0, TCP_OPEN_SERVER, HTTP_PORT, TCP_PURPOSE_HTTP_SERVER);
    #if defined(STACK_USE_SSL_SERVER)
    TCPAddSSLListener(activeSocket, HTTPS_PORT);
    #endif
    
      // Save the default record (just invalid file handles)
    // oldPtr = MACSetWritePtr(BASE_HTTPB_ADDR + activeConnectionID*sizeof(HTTP_SERVER_REQUEST));
    // MACPutArray((BYTE*)&currentRequest, sizeof(HTTP_SERVER_REQUEST));
    // MACSetWritePtr(oldPtr);
  }

  // Set activeConnectionID to zero so that first call to HTTPLoadConn() doesn't write 
  // dummy data outside reserved HTTP memory.
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
    
    // Save the old one
  // oldPtr = MACSetWritePtr(BASE_HTTPB_ADDR + activeConnectionID*sizeof(HTTP_SERVER_REQUEST));
  // MACPutArray((BYTE*)&currentRequest, sizeof(HTTP_SERVER_REQUEST));
  // MACSetWritePtr(oldPtr);
  
  // // Load the new one
  // oldPtr = MACSetReadPtr(BASE_HTTPB_ADDR + hHTTP*sizeof(HTTP_SERVER_REQUEST));
  // MACGetArray((BYTE*)&currentRequest, sizeof(HTTP_SERVER_REQUEST));
  // MACSetReadPtr(oldPtr);

  //activeConnection = httpConnections[hHTTP];
  
  // Remember which one is loaded
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

// #ifdef STACK_USE_MDD 
//  SearchRec rec;
//     unsigned char attributes;
//  BYTE j,cntr=0;
//  BYTE * dummyPtr=NULL;
//  BYTE * ptr = NULL;
//  BYTE * tempPtr=NULL;
//  BYTE dummyCntr;
//  signed char chdirRetVal;
// #endif


//#ifdef STACK_USE_MDD  
  if(!SDCARD_IsCardInserted())
  { 
    activeResponse.status = HTTP_NOT_FOUND;
    activeConnectionState = SM_HTTP_HANDLE_ERROR;

    // Check for 404. File Not Found
    //curHTTP.file = NULL;

    // if(tempPtr != NULL)
    //  free(tempPtr);
    // if(directoryPtr != NULL)
    // {  
    //  free(directoryPtr); 
    //  directoryPtr=NULL;
    // }
  }
//#endif



  do
  {
    isDone = TRUE;

    switch(activeConnectionState)
    {

      case SM_HTTP_IDLE:

        // Check how much data is waiting
        lenA = TCPIsGetReady(activeSocket);

        // If a connection has been made, then process the request
        if(lenA)
        {// Clear out state info and move to next state

          activeResponse.status = HTTP_OK;
          activeResponse.returnType = HTTP_UNKNOWN;
          activeResponse.disableCache = FALSE;

          activeRequest.method = HTTP_GET;
          activeRequest.url[0] = '\0';
          activeRequest.methodState = 0x00;
          activeRequest.contentLength = 0;
          
          activeConnection.wdTimer = TickGet() + HTTP_TIMEOUT*TICK_SECOND;
          activeConnection.bytesAvailable = 0xffffffff;
          activeConnection.data[0] = '\0';
          
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
        if(lenA > 6u)
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

        // Find end of filename
        lenA = TCPFind(activeSocket, ' ', 0, FALSE);
        //lenB = TCPFindEx(sktHTTP, '?', 0, lenA, FALSE);
        //lenA = mMIN(lenA, lenB);
        
        // If the file name is too long, then reject the request
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
        //HTTPURLDecode(activeConnection.data);

        // Decode may have changed the string length - update it here
        //lenB = strlen((char*)currentRequest.data);


// #ifdef STACK_USE_MDD   

//      //Calculate 2 Bytes HashIndex for  curHTTP.file->name
//      // Calculate the name hash to speed up searching
//      for(nameHash = 0, ptr = (BYTE*)(&curHTTP.data[1]); ptr !=(BYTE*) (&curHTTP.data[lenB]); ptr++)
//      {
//        if(*ptr != 0x20)
//        {
//          nameHash += *ptr;
//          nameHash <<= 1;
//        }
//      }
// #endif
      
      // // Find the extension in the filename
      // for(ext = curHTTP.data + lenB-1; ext != curHTTP.data; ext--)
      //  if(*ext == '.')
      //    break;
          
      // // Compare to known extensions to determine Content-Type
      // ext++;
      // for(curHTTP.fileType = HTTP_TXT; curHTTP.fileType < HTTP_UNKNOWN; curHTTP.fileType++)
      //  if(!stricmppgm2ram(ext, (ROM void*)httpFileExtensions[curHTTP.fileType]))
      //    break;
      
      // Perform first round authentication
      // #if defined(HTTP_USE_AUTHENTICATION)
      // currentRequest.isAuthorized = HTTPNeedsAuth(&currentRequest.data[0]);
      // #endif


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
    
      /*#if defined(HTTP_USE_AUTHENTICATION)
      // Check current authorization state
      if(currentRequest.isAuthorized < 0x80)
      {// 401 error
        currentRequest.status = HTTP_UNAUTHORIZED;
        activeConnectionState = SM_HTTP_SERVE_HEADERS;
        isDone = FALSE;
        
        #if defined(HTTP_NO_AUTH_WITHOUT_SSL)
        if(!TCPIsSSL(activeSocket))
          currentRequest.status = HTTP_SSL_REQUIRED;
        #endif

        break;
      }
      #endif*/

      // Parse the args string
      //*curHTTP.ptrData = '\0';
      //curHTTP.ptrData = HTTPURLDecode(curHTTP.data);
      
      // Move on to GET args, unless there are none
      if(activeRequest.method == HTTP_GET)
        activeConnectionState = SM_HTTP_PROCESS_GET;
      else
        activeConnectionState = SM_HTTP_PROCESS_POST;

      isDone = FALSE;
      //curHTTP.hasArgs = FALSE;
      break;

    case SM_HTTP_PROCESS_GET:

      // Run the application callback HTTPExecuteGet()
      if(HTTPExecuteRoute() == HTTP_IO_WAITING)
      {// If waiting for asynchronous process, return to main app
        break;
      }

      // Move on to POST data
      //smHTTP = SM_HTTP_PROCESS_POST;
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
        c = HTTPExecuteRoute();
        
        // If waiting for asynchronous process, return to main app
        if(c == (BYTE)HTTP_IO_WAITING)
        {// return to main app and make sure we don't get stuck by the watchdog
          activeConnection.bytesAvailable = TCPIsGetReady(activeSocket) - 1;
          break;
        }
        else if(c == (BYTE)HTTP_IO_NEED_DATA)
        {// If waiting for more data
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
      // No break, continue to sending request

    case SM_HTTP_HANDLE_ERROR:

      mLED_Yellow_On();
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
  static BOOL HTTPSendFile(void)

  Description:
  Serves up the next chunk of curHTTP's file, up to a) available TX FIFO
  space or b) the next callback index, whichever comes first.

  Precondition:
  curHTTP.file and curHTTP.offsets have both been opened for reading.

  Parameters:
  None

  Return Values:
  TRUE - the end of the file was reached and reading is done
  FALSE - more data remains to be read
  ***************************************************************************/
// static BOOL HTTPSendFile(void)
// {

// #ifdef STACK_USE_MDD

//   static DWORD availbleTcpBuffSize,len;
//   static DWORD cntr=0;
//   static BYTE lock=0;
//   static BYTE nameHashMatched=FALSE;
//   static DWORD numBytes,dynVarCntr,dynVarRcrdOffset,dynVarCallBackID,bytesReadCount=0;
//   DWORD UInt32DataFromBinFile;
//   WORD UInt16DataFromBinFile,nameHashRcrd;
//   DWORD recrdcntr=0;
  
//   signed char chdirRetVal;

//   static enum
//   {
//     SM_IDLE = 0u,
//     SM_GET_NO_OF_FILES,       //0x1 
//     SM_GET_HASH_RCRD,       //0x2
//     SM_COMPARE_HASH_RCRD,     //0x3
//     SM_GET_DYN_VAR_FILE_RCRD,
//     SM_PARSE_TILL_DYN_VAR,    //0x4
//     SM_PARSE_DYN_VAR_STRING,
//     SM_PROCESS_DYN_VAR_CALLBACK,        //0x5
//     SM_SERVE_TEXT_DATA,     //0x6

//   }smHTTPSendFile = SM_IDLE;

//   switch(smHTTPSendFile)
//   {
//     case SM_IDLE:

//       if(CurWorkDirChangedToMddRootPath == FALSE && directoryPtr!= NULL )
//       {
//         chdirRetVal=FSchdir(MDD_ROOT_DIR_PATH);
          
//         if(chdirRetVal==0)
//         { 
//           CurWorkDirChangedToMddRootPath =TRUE;
//         }
//         else
//         {
//           free(directoryPtr);
//           return TRUE;
//         }
        
//       }
    
//       numBytes=(*(curHTTP.file)).size;
      
//     case SM_GET_NO_OF_FILES:
//       FileRcrdPtr=FSfopen(filename, "r");
//       cntr=FileReadUInt32(&recrdcntr,FileRcrdPtr);//Reading Number of files in record
      
//       //Continue to next state
//       smHTTPSendFile = SM_GET_HASH_RCRD;
            
//     case SM_GET_HASH_RCRD:

//       while(recrdcntr)
//       {
//         cntr=FileReadUInt16(&nameHashRcrd,FileRcrdPtr);//Reading HashName record  
        
//         if(nameHash == nameHashRcrd)
//         {
//           nameHashMatched=TRUE;
//           DynVarRcrdFilePtr=FSfopen(dynVarRcrdFileName, "r");

//           //Reading OFFSET of dynvar records in dynvarrcrd.bin
//           cntr=FileReadUInt32(&UInt32DataFromBinFile,FileRcrdPtr);
        
//           FileSeek(DynVarRcrdFilePtr,UInt32DataFromBinFile,SEEK_SET);

//           //Reading Number dynamic variables in the file 
//           cntr=FileReadUInt32(&dynVarCntr,FileRcrdPtr);
//           break;
//         }
//         else //Dummy Read..to hop to next hash name or HOP by "FileSeek" in file handle 
//         { 
//           cntr=FileReadUInt32(&UInt32DataFromBinFile,FileRcrdPtr);
//           cntr=FileReadUInt32(&UInt32DataFromBinFile,FileRcrdPtr);
//         }
//         recrdcntr-=1;
    
//       }

//       if(FileRcrdPtr != NULL)
//         FileClose(FileRcrdPtr);

//       if(nameHashMatched == TRUE)
//       {
//         //Continue to next state
//         smHTTPSendFile = SM_GET_DYN_VAR_FILE_RCRD; 
//       }

//       //If NO HashName record matched means the requrested webpage do not have dynamic variables
//       if(recrdcntr == 0 && nameHashMatched !=TRUE )
//       {
//         smHTTPSendFile=SM_SERVE_TEXT_DATA ;

//         if(DynVarRcrdFilePtr != NULL)
//         FileClose(DynVarRcrdFilePtr);
//         break;
//       }

//     case SM_GET_DYN_VAR_FILE_RCRD:
      
//       if(lock==0)
//       {
//         cntr=FileReadUInt32(&UInt32DataFromBinFile,DynVarRcrdFilePtr);//Reading Record Length 
//         cntr=FileReadUInt16(&UInt16DataFromBinFile,DynVarRcrdFilePtr);//Reading Flags
//         lock=1;
//       }
      
//       cntr=FileReadUInt32(&dynVarRcrdOffset,DynVarRcrdFilePtr);//Reading dynamic variable offset in webpage     
//       cntr=FileReadUInt32(&dynVarCallBackID,DynVarRcrdFilePtr);//Reading dynamic variable call back ID  
      
        
//       //Continue to next state
//       smHTTPSendFile =SM_PARSE_TILL_DYN_VAR;
      
//     case SM_PARSE_TILL_DYN_VAR:
        
//       //If the dynamic variable starts at the begining of any file, Parse the dynamic var string
//       if( dynVarRcrdOffset== 0x00)
//       {
//         smHTTPSendFile = SM_PARSE_DYN_VAR_STRING;
//       }
//       else
//       {

//         // Determine and keep parsing data depending on the number of bytes available in the TCP transmit buffer 
//         availbleTcpBuffSize = TCPIsPutReady(sktHTTP);

//         if(availbleTcpBuffSize >= 64)
//         {
//           if((dynVarRcrdOffset-bytesReadCount) >= 64)
//           {
//             len=FSfread(sendDataBuffer, 64, 1, curHTTP.file);
//             TCPPutArray(sktHTTP, sendDataBuffer, 64);
//             numBytes -=64;
//             bytesReadCount+=64;
//           }
//           else
//           {
//             len=FSfread(sendDataBuffer, (dynVarRcrdOffset-bytesReadCount), 1, curHTTP.file);
    
//             TCPPutArray(sktHTTP, sendDataBuffer, (dynVarRcrdOffset-bytesReadCount));
//             numBytes -=(dynVarRcrdOffset-bytesReadCount);
//             bytesReadCount+=(dynVarRcrdOffset-bytesReadCount);
//           }
//         }
//         else if(availbleTcpBuffSize != 0)
//         {
//           if(bytesReadCount != dynVarRcrdOffset )
//           {
//             if((dynVarRcrdOffset-bytesReadCount) >= availbleTcpBuffSize)
//             {
//               len=FSfread(sendDataBuffer, availbleTcpBuffSize, 1, curHTTP.file);
//               TCPPutArray(sktHTTP, sendDataBuffer, availbleTcpBuffSize);
//               numBytes -=availbleTcpBuffSize;
//               bytesReadCount+=availbleTcpBuffSize;
//             }
//             else
//             {
//               len=FSfread(sendDataBuffer, (dynVarRcrdOffset-bytesReadCount), 1, curHTTP.file);
//               TCPPutArray(sktHTTP, sendDataBuffer, (dynVarRcrdOffset-bytesReadCount));
//               numBytes -=(dynVarRcrdOffset-bytesReadCount);
//               bytesReadCount+=(dynVarRcrdOffset-bytesReadCount);
//             }
//           }
//         }
//       }

//       if(dynVarRcrdOffset == bytesReadCount)
//       {
//         //Continue to next state
//         smHTTPSendFile = SM_PARSE_DYN_VAR_STRING;
//       }

//       break;

//     case SM_PARSE_DYN_VAR_STRING:

//       len=FSfread(sendDataBuffer, 1, 1, curHTTP.file);
//       numBytes-=1;
//       bytesReadCount+=1;
//       if(sendDataBuffer[0]=='~')
//       {
//         do
//         {
//           len=FSfread(sendDataBuffer, 1, 1, curHTTP.file);
//           numBytes-=1;
//           bytesReadCount+=1;
//         }
//         while(sendDataBuffer[0]!='~');
//       }

//       //Continue to next state to process the dynamic variable callback
//       smHTTPSendFile =SM_PROCESS_DYN_VAR_CALLBACK;
      
      
//     case SM_PROCESS_DYN_VAR_CALLBACK:
      
//       EndOfCallBackFileFlag = TRUE;

//       if(CurWorkDirChangedToMddRootPath == FALSE  && directoryPtr!= NULL)
//       {
//         chdirRetVal=FSchdir(MDD_ROOT_DIR_PATH);
          
//         if(chdirRetVal==0)
//         { 
//           CurWorkDirChangedToMddRootPath =TRUE;
//         }
//         else
//         {
//           free(directoryPtr);
//           return TRUE;
//         }
        
//       }
//       if(dynVarCallBackID == 2)
//       {
//         dynVarCallBackID=dynVarCallBackID;
//       }
  
//       HTTPPrint(dynVarCallBackID);
//       TCPFlush(sktHTTP);

//       if(CurWorkDirChangedToMddRootPath == TRUE  && directoryPtr!= NULL)
//       {
      
//           //Change working directory to client request directory
//           chdirRetVal=FSchdir((char *)(directoryPtr+2));
//           if(chdirRetVal==0)
//           {
//             CurWorkDirChangedToMddRootPath=FALSE;   
//           }
//           else
//           {
//             free(directoryPtr);
//             return TRUE;
//           }
          
        
//       }

//       if(EndOfCallBackFileFlag == TRUE)
//       {
//         dynVarCntr-=1;
//         smHTTPSendFile=SM_GET_DYN_VAR_FILE_RCRD;
//         if(dynVarCntr == 0)
//         {
//           if((!FSfeof(curHTTP.file))||(numBytes != 0))
//           {   
//             smHTTPSendFile =SM_SERVE_TEXT_DATA;
          
//           }

//           lock=0; 

//         } 
        
//       }
      
//       break;
      
//     case SM_SERVE_TEXT_DATA:

//       // If HashIndex do not match,that means no entry in the "FilRcrd.bin", means no dynamic variables for this wepage,
//       //then proceed to serve the page as normal HTML text

//       availbleTcpBuffSize = TCPIsPutReady(sktHTTP);
      
//       if(availbleTcpBuffSize >= 64)
//       {
//         if(numBytes >= 64)
//         {
//           len=FSfread(sendDataBuffer, 64, 1, curHTTP.file);
//           TCPPutArray(sktHTTP, sendDataBuffer, 64);
//           numBytes -=64;
//         }
//         else
//         {
//           len=FSfread(sendDataBuffer, numBytes, 1, curHTTP.file);
//           TCPPutArray(sktHTTP, sendDataBuffer, numBytes);
//           numBytes=0;

//         }
//       }
//       else if(availbleTcpBuffSize != 0)
//       {
//         if(numBytes >= availbleTcpBuffSize)
//         {
//           len=FSfread(sendDataBuffer, availbleTcpBuffSize, 1, curHTTP.file);
//           TCPPutArray(sktHTTP, sendDataBuffer, availbleTcpBuffSize);
//           numBytes -=availbleTcpBuffSize;
//         }
//         else 
//         {
//           len=FSfread(sendDataBuffer, numBytes, 1, curHTTP.file);
//           TCPPutArray(sktHTTP, sendDataBuffer, numBytes);
//           numBytes=0;
          
//         }
//       }
//       if(numBytes <= 100)
//       {
//         numBytes=numBytes;
//       }
//       if(numBytes == 0)
//       {
//         TCPFlush(sktHTTP);

      
//         if(curHTTP.offsets != INVALID_FILE_HANDLE)
//         {
//           FileClose(curHTTP.offsets);
//           curHTTP.offsets = INVALID_FILE_HANDLE;
//         }
//         nameHashMatched = FALSE;

//         if(DynVarRcrdFilePtr != NULL)
//         FileClose(DynVarRcrdFilePtr);
      
//         if(CurWorkDirChangedToMddRootPath == FALSE  && directoryPtr!= NULL)
//         {
//             chdirRetVal=FSchdir(MDD_ROOT_DIR_PATH);
          
//             if(chdirRetVal==0)
//             { 
//               CurWorkDirChangedToMddRootPath =TRUE;
//             }
//             else
//             {
//               free(directoryPtr);
//               return TRUE;
//             }
//         }

//         smHTTPSendFile=SM_IDLE;
//         bytesReadCount=0;
//         return TRUE;
//       }
//       break;

//     default:
//       return FALSE;
        
//   }

//   if((FSfeof(curHTTP.file) || (numBytes == 0))&& EndOfCallBackFileFlag == TRUE)
//   {
//     TCPFlush(sktHTTP);

    
//     FileClose(curHTTP.offsets);
//     nameHashMatched = FALSE;
//     lock=0;
    
//     if(DynVarRcrdFilePtr!= NULL)
//       FileClose(DynVarRcrdFilePtr);
        
//     if(CurWorkDirChangedToMddRootPath == FALSE  && directoryPtr!= NULL)
//     {
//         chdirRetVal=FSchdir(MDD_ROOT_DIR_PATH);
          
//         if(chdirRetVal==0)
//         { 
//           CurWorkDirChangedToMddRootPath =TRUE;
//         }
//         else
//         {
//           free(directoryPtr);
//           return TRUE;
//         }
//     } 

            
//     smHTTPSendFile=SM_IDLE;
//     return TRUE;
//   }

//   return FALSE;
// #else

//   WORD numBytes, len;
//   BYTE c, data[64];
  
//   // Determine how many bytes we can read right now
//   len = TCPIsPutReady(sktHTTP);
//   numBytes = mMIN(len, curHTTP.nextCallback - curHTTP.byteCount);
  
//   // Get/put as many bytes as possible
//   curHTTP.byteCount += numBytes;
//   while(numBytes > 0u)
//   {
//     len = MPFSGetArray(curHTTP.file, data, mMIN(numBytes, 64u));
//     if(len == 0u)
//       return TRUE;
//     else
//       TCPPutArray(sktHTTP, data, len);
//     numBytes -= len;
//   }
  
//   // Check if a callback index was reached
//   if(curHTTP.byteCount == curHTTP.nextCallback)
//   {
//     // Update the state machine
//     smHTTP = SM_HTTP_SEND_FROM_CALLBACK;
//     curHTTP.callbackPos = 0;

//     // Read past the variable name and close the MPFS
//     MPFSGet(curHTTP.file, NULL);
//     do
//     {
//       if(!MPFSGet(curHTTP.file, &c))
//         break;
//       curHTTP.byteCount++;
//     } while(c != '~');
//     curHTTP.byteCount++;
    
//     // Read in the callback address and next offset
//     MPFSGetLong(curHTTP.offsets, &(curHTTP.callbackID));
//     if(!MPFSGetLong(curHTTP.offsets, &(curHTTP.nextCallback)))
//     {
//       curHTTP.nextCallback = 0xffffffff;
//       MPFSClose(curHTTP.offsets);
//       curHTTP.offsets = MPFS_INVALID_HANDLE;
//     }
//   }

//     // We are not done sending a file yet...
//     return FALSE;

// #endif
  
// }

/*****************************************************************************
  Function:
  static void HTTPHeaderParseLookup(BYTE i)

  Description:
  Calls the appropriate header parser based on the index of the header
  that was read from the request.

  Precondition:
  None

  Parameters:
  i - the index of the string found in HTTPRequestHeaders

  Return Values:
  TRUE - the end of the file was reached and reading is done
  FALSE - more data remains to be read
  ***************************************************************************/
// static void HTTPHeaderParseLookup(BYTE i)
// {
//   // i corresponds to an index in HTTPRequestHeaders
  
//   #if defined(HTTP_USE_COOKIES)
//   if(i == 0u)
//   {
//     HTTPHeaderParseCookie();
//     return;
//   }
//   #endif
  
//   #if defined(HTTP_USE_AUTHENTICATION)  
//   if(i == 1u)
//   {
//     HTTPHeaderParseAuthorization();
//     return;
//   }
//   #endif
  
//   #if defined(HTTP_USE_POST)
//   if(i == 2u)
//   {
//     HTTPHeaderParseContentLength();
//     return;
//   }
//   #endif
// }

/*****************************************************************************
  Function:
  static void HTTPHeaderParseAuthorization(void)

  Summary:
  Parses the "Authorization:" header for a request and verifies the
  credentials.

  Description:
  Parses the "Authorization:" header for a request.  For example, 
  "BASIC YWRtaW46cGFzc3dvcmQ=" is decoded to a user name of "admin" and
  a password of "password".  Once read, HTTPCheckAuth is called from
  CustomHTTPApp.c to determine if the credentials are acceptable.

  The return value of HTTPCheckAuth is saved in curHTTP.isAuthorized for
  later use by the application.

  Precondition:
  None

  Parameters:
  None

  Returns:
  None

  Remarks:
  This function is ony available when HTTP_USE_AUTHENTICATION is defined.
  ***************************************************************************/
// #if defined(HTTP_USE_AUTHENTICATION)
// static void HTTPHeaderParseAuthorization(void)
// {
//     WORD len;
//     BYTE buf[40];
//   BYTE *ptrBuf;
  
//   // If auth processing is not required, return
//   if(curHTTP.isAuthorized & 0x80)
//     return;

//   // Clear the auth type ("BASIC ")
//   TCPGetArray(sktHTTP, NULL, 6);

//   // Find the terminating CRLF and make sure it's a multiple of four
//   len = TCPFindROMArray(sktHTTP, HTTP_CRLF, HTTP_CRLF_LEN, 0, FALSE);
//   len += 3;
//   len &= 0xfc;
//   len = mMIN(len, sizeof(buf)-4);
  
//   // Read in 4 bytes at a time and decode (slower, but saves RAM)
//   for(ptrBuf = buf; len > 0u; len-=4, ptrBuf+=3)
//   {
//     TCPGetArray(sktHTTP, ptrBuf, 4);
//     Base64Decode(ptrBuf, 4, ptrBuf, 3);
//   }

//   // Null terminate both, and make sure there's at least two terminators
//   *ptrBuf = '\0';
//   for(len = 0, ptrBuf = buf; len < sizeof(buf); len++, ptrBuf++)
//     if(*ptrBuf == ':')
//       break;
//   *(ptrBuf++) = '\0';
  
//   // Verify credentials
//   curHTTP.isAuthorized = HTTPCheckAuth(buf, ptrBuf);

//   return;
// }
// #endif

/*****************************************************************************
  Function:
  static void HTTPHeaderParseCookie(void)

  Summary:
  Parses the "Cookie:" headers for a request and stores them as GET
  variables.

  Description:
  Parses the "Cookie:" headers for a request.  For example, 
  "Cookie: name=Wile+E.+Coyote; order=ROCKET_LAUNCHER" is decoded to 
  "name=Wile+E.+Coyote&order=ROCKET_LAUNCHER&" and stored as any other 
  GET variable in curHTTP.data.

  The user application can easily access these values later using the
  HTTPGetArg() and HTTPGetROMArg() functions.

  Precondition:
  None

  Parameters:
  None

  Returns:
  None

  Remarks:
  This function is ony available when HTTP_USE_COOKIES is defined.
  ***************************************************************************/
// #if defined(HTTP_USE_COOKIES)
// static void HTTPHeaderParseCookie(void)
// {
//   WORD lenA, lenB;

//   // Verify there's enough space
//   lenB = TCPFindROMArray(sktHTTP, HTTP_CRLF, HTTP_CRLF_LEN, 0, FALSE);
//   if(lenB >= (WORD)(curHTTP.data + HTTP_MAX_DATA_LEN - curHTTP.ptrData - 2))
//   {// If not, overflow
//     curHTTP.httpStatus = HTTP_OVERFLOW;
//     smHTTP = SM_HTTP_SERVE_HEADERS;
//     return;
//   }

//   // While a CRLF is not immediate, grab a cookie value
//   while(lenB != 0u)
//   {
//     // Look for a ';' and use the shorter of that or a CRLF
//     lenA = TCPFind(sktHTTP, ';', 0, FALSE);
    
//     // Read to the terminator
//     curHTTP.ptrData += TCPGetArray(sktHTTP, curHTTP.ptrData, mMIN(lenA, lenB));
    
//     // Insert an & to anticipate another cookie
//     *(curHTTP.ptrData++) = '&';
    
//     // If semicolon, trash it and whitespace
//     if(lenA < lenB)
//     {
//       TCPGet(sktHTTP, NULL);
//       while(TCPFind(sktHTTP, ' ', 0, FALSE) == 0u)
//         TCPGet(sktHTTP, NULL);
//     }
    
//     // Find the new distance to the CRLF
//     lenB = TCPFindROMArray(sktHTTP, HTTP_CRLF, HTTP_CRLF_LEN, 0, FALSE);
//   }

//   return;

// }
// #endif

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

/*****************************************************************************
  Function:
  BYTE* HTTPURLDecode(BYTE* cData)

  Summary:
  Parses a string from URL encoding to plain-text.

  Description:
  Parses a string from URL encoding to plain-text.  The following
  conversions are made: ‘=’ to ‘\0’, ‘&’ to ‘\0’, ‘+’ to ‘ ‘, and
  “%xx” to a single hex byte.
 
  After completion, the data has been decoded and a null terminator
  signifies the end of a name or value.  A second null terminator (or a
  null name parameter) indicates the end of all the data.

  Precondition:
  The data parameter is null terminated and has at least one extra
  byte free.

  Parameters:
  cData - The string which is to be decoded in place.

  Returns:
  A pointer to the last null terminator in data, which is also the
  first free byte for new data.

  Remarks:
  This function is called by the stack to parse GET arguments and 
  cookie data.  User applications can use this function to decode POST
  data, but first need to verify that the string is null-terminated.
  ***************************************************************************/
// BYTE* HTTPURLDecode(BYTE* cData)
// {
//   BYTE *pRead, *pWrite;
//   WORD wLen;
//   BYTE c;
//   WORD_VAL hex;
   
//   // Determine length of input
//   wLen = strlen((char*)cData);
   
//   // Read all characters in the string
//   for(pRead = pWrite = cData; wLen != 0u; )
//   {
//     c = *pRead++;
//     wLen--;
    
//     if(c == '=' || c == '&')
//       *pWrite++ = '\0';
//     else if(c == '+')
//       *pWrite++ = ' ';
//     else if(c == '%')
//     {
//       if(wLen < 2u)
//         wLen = 0;
//       else
//       {
//         hex.v[1] = *pRead++;
//         hex.v[0] = *pRead++;
//         wLen--;
//         wLen--;
//         *pWrite++ = hexatob(hex);
//       }
//     }
//     else
//       *pWrite++ = c;
//   }
  
//   // Double null terminate the last value
//   *pWrite++ = '\0';
//   *pWrite = '\0';
  
//   return pWrite;
// }

/*****************************************************************************
  Function:
  BYTE* HTTPGetArg(BYTE* cData, BYTE* cArg)

  Summary:
  Locates a form field value in a given data array.

  Description:
  Searches through a data array to find the value associated with a
  given argument.  It can be used to find form field values in data
  received over GET or POST.
  
  The end of data is assumed to be reached when a null name parameter is
  encountered.  This requires the string to have an even number of 
  null-terminated strings, followed by an additional null terminator.

  Precondition:
  The data array has a valid series of null terminated name/value pairs.

  Parameters:
  data - the buffer to search
  arg - the name of the argument to find

  Returns:
  A pointer to the argument value, or NULL if not found.
  ***************************************************************************/
// BYTE* HTTPGetArg(BYTE* cData, BYTE* cArg)
// {
//   // Search through the array while bytes remain
//   while(*cData != '\0')
//   { 
//     // Look for arg at current position
//     if(!strcmp((char*)cArg, (char*)cData))
//     {// Found it, so return parameter
//       return cData + strlen((char*)cArg) + 1;
//     }
    
//     // Skip past two strings (NUL bytes)
//     cData += strlen((char*)cData) + 1;
//     cData += strlen((char*)cData) + 1;
//   }
    
//   // Return NULL if not found
//   return NULL;
// }

/*****************************************************************************
  Function:
  BYTE* HTTPGetROMArg(BYTE* cData, ROM BYTE* cArg)

  Summary:
  Locates a form field value in a given data array.

  Description:
  Searches through a data array to find the value associated with a
  given argument.  It can be used to find form field values in data
  received over GET or POST.
  
  The end of data is assumed to be reached when a null name parameter is
  encountered.  This requires the string to have an even number of 
  null-terminated strings, followed by an additional null terminator.

  Precondition:
  The data array has a valid series of null terminated name/value pairs.

  Parameters:
  data - the buffer to search
  arg - the name of the argument to find

  Returns:
  A pointer to the argument value, or NULL if not found.

  Remarks:
    This function is aliased to HTTPGetArg on non-PIC18 platforms.
  ***************************************************************************/
// #if defined(__18CXX)
// BYTE* HTTPGetROMArg(BYTE* cData, ROM BYTE* cArg)
// {
//   // Search through the array while bytes remain
//   while(*cData != '\0')
//   {
//     // Look for arg at current position
//     if(!memcmppgm2ram(cData, (ROM void*)cArg, strlenpgm((ROM char*)cArg) + 1))
//     {// Found it, so skip to next string
//       return cData + strlenpgm((ROM char*)cArg) + 1;
//     }
    
//     // Skip past two strings (NUL bytes)
//     cData += strlen((char*)cData) + 1;
//     cData += strlen((char*)cData) + 1;
//   }
    
//   // Return NULL if not found
//   return NULL;
// }
// #endif

/*****************************************************************************
  Function:
  HTTP_READ_STATUS HTTPReadPostName(BYTE* cData, WORD wLen)

  Summary:
  Reads a name from a URL encoded string in the TCP buffer.

  Description:
  Reads a name from a URL encoded string in the TCP buffer.  This function
  is meant to be called from an HTTPExecutePost callback to facilitate
  easier parsing of incoming data.  This function also prevents buffer
  overflows by forcing the programmer to indicate how many bytes are
  expected.  At least 2 extra bytes are needed in cData over the maximum
  length of data expected to be read.
  
  This function will read until the next '=' character, which indicates the
  end of a name parameter.  It assumes that the front of the buffer is
  the beginning of the name paramter to be read.
  
  This function properly updates curHTTP.byteCount by decrementing it
  by the number of bytes read.  It also removes the delimiting '=' from
  the buffer.

  Precondition:
  Front of TCP buffer is the beginning of a name parameter, and the rest of
  the TCP buffer contains a URL-encoded string with a name parameter 
  terminated by a '=' character.

  Parameters:
  cData - where to store the name once it is read
  wLen - how many bytes can be written to cData

  Return Values:
  HTTP_READ_OK - name was successfully read
  HTTP_READ_TRUNCTATED - entire name could not fit in the buffer, so the
              value was truncated and data has been lost
  HTTP_READ_INCOMPLETE - entire name was not yet in the buffer, so call
              this function again later to retrieve
  ***************************************************************************/
// #if defined(HTTP_USE_POST)
// HTTP_READ_STATUS HTTPReadPostName(BYTE* cData, WORD wLen)
// {
//   HTTP_READ_STATUS status;
  
//   status = HTTPReadTo('=', cData, wLen);

//   // Decode the data (if not reading to null or blank) and return
//   if(cData && *cData)
//     HTTPURLDecode(cData);
//   return status;
// } 
// #endif

/*****************************************************************************
  Function:
  HTTP_READ_STATUS HTTPReadPostValue(BYTE* cData, WORD wLen)

  Summary:
  Reads a value from a URL encoded string in the TCP buffer.

  Description:
  Reads a value from a URL encoded string in the TCP buffer.  This function
  is meant to be called from an HTTPExecutePost callback to facilitate
  easier parsing of incoming data.  This function also prevents buffer
  overflows by forcing the programmer to indicate how many bytes are
  expected.  At least 2 extra bytes are needed in cData above the maximum
  length of data expected to be read.
  
  This function will read until the next '&' character, which indicates the
  end of a value parameter.  It assumes that the front of the buffer is
  the beginning of the value paramter to be read.  If curHTTP.byteCount
  indicates that all expected bytes are in the buffer, it assumes that 
  all remaining data is the value and acts accordingly.
  
  This function properly updates curHTTP.byteCount by decrementing it
  by the number of bytes read.  The terminating '&' character is also 
  removed from the buffer.
  
  Precondition:
  Front of TCP buffer is the beginning of a name parameter, and the rest of
  the TCP buffer contains a URL-encoded string with a name parameter 
  terminated by a '=' character.

  Parameters:
  cData - where to store the value once it is read
  wLen - how many bytes can be written to cData

  Return Values:
  HTTP_READ_OK - value was successfully read
  HTTP_READ_TRUNCTATED - entire value could not fit in the buffer, so the
              value was truncated and data has been lost
  HTTP_READ_INCOMPLETE - entire value was not yet in the buffer, so call
              this function again later to retrieve
  ***************************************************************************/
// #if defined(HTTP_USE_POST)
// HTTP_READ_STATUS HTTPReadPostValue(BYTE* cData, WORD wLen)
// {
//   HTTP_READ_STATUS status;
  
//   // Try to read the value
//   status = HTTPReadTo('&', cData, wLen);
  
//   // If read was incomplete, check if we're at the end
//   if(status == HTTP_READ_INCOMPLETE)
//   {
//     // If all data has arrived, read all remaining data
//     if(curHTTP.byteCount == TCPIsGetReady(sktHTTP))
//       status = HTTPReadTo('\0', cData, wLen);
//   }
    
//   // Decode the data (if not reading to null or blank) and return
//   if(cData && *cData)
//     HTTPURLDecode(cData);
//   return status;
// } 
// #endif

/*****************************************************************************
  Function:
  static HTTP_READ_STATUS HTTPReadTo(BYTE cDelim, BYTE* cData, WORD wLen)

  Summary:
  Reads to a buffer until a specified delimiter character.

  Description:
  Reads from the TCP buffer to cData until either cDelim is reached, or
  until wLen - 2 bytes have been read.  The value read is saved to cData and 
  null terminated.  (wLen - 2 is used so that the value can be passed to
  HTTPURLDecode later, which requires a null terminator plus one extra free
  byte.)
  
  The delimiter character is removed from the buffer, but not saved to 
  cData. If all data cannot fit into cData, it will still be removed from 
  the buffer but will not be saved anywhere.

  This function properly updates curHTTP.byteCount by decrementing it
  by the number of bytes read. 

  Precondition:
  None

  Parameters:
    cDelim - the character at which to stop reading, or NULL to read to
         the end of the buffer
  cData - where to store the data being read
  wLen - how many bytes can be written to cData

  Return Values:
  HTTP_READ_OK - data was successfully read
  HTTP_READ_TRUNCTATED - entire data could not fit in the buffer, so the
              data was truncated and data has been lost
  HTTP_READ_INCOMPLETE - delimiter character was not found
  ***************************************************************************/
// #if defined(HTTP_USE_POST)
// static HTTP_READ_STATUS HTTPReadTo(BYTE cDelim, BYTE* cData, WORD wLen)
// {
//   HTTP_READ_STATUS status;
//   WORD wPos;
  
//   // Either look for delimiter, or read all available data
//   if(cDelim)
//     wPos = TCPFind(sktHTTP, cDelim, 0, FALSE);
//   else
//     wPos = TCPIsGetReady(sktHTTP);
  
//   // If not found, return incomplete
//   if(wPos == 0xffff)
//     return HTTP_READ_INCOMPLETE;
  
//   // Read the value
//   if(wLen < 2u && cData != NULL)
//   {// Buffer is too small, so read to NULL instead
//     curHTTP.byteCount -= TCPGetArray(sktHTTP, NULL, wPos);
//     status = HTTP_READ_TRUNCATED;
//   }
//   else if(cData == NULL)
//   {// Just remove the data
//     curHTTP.byteCount -= TCPGetArray(sktHTTP, NULL, wPos);
//     status = HTTP_READ_OK;
//   }
//   else if(wPos > wLen - 2)
//   {// Read data, but truncate at max length
//     curHTTP.byteCount -= TCPGetArray(sktHTTP, cData, wLen - 2);
//     curHTTP.byteCount -= TCPGetArray(sktHTTP, NULL, wPos - (wLen - 2));
//     cData[wLen - 2] = '\0';
//     status = HTTP_READ_TRUNCATED;
//   }
//   else
//   {// Read the data normally
//     curHTTP.byteCount -= TCPGetArray(sktHTTP, cData, wPos);
//     cData[wPos] = '\0';
//     status = HTTP_READ_OK;
//   }
  
//   // Remove the delimiter
//   if(cDelim)
//     curHTTP.byteCount -= TCPGet(sktHTTP, NULL);
  
//   return status;
// } 
// #endif


/*****************************************************************************
  Function:
  void HTTPIncFile(ROM BYTE* cFile)

  Summary:
  Writes a file byte-for-byte to the currently loaded TCP socket.

  Description:
  Allows an entire file to be included as a dynamic variable, providing
  a basic templating system for HTML web pages.  This reduces unneeded
  duplication of visual elements such as headers, menus, etc.

  When curHTTP.callbackPos is 0, the file is opened and as many bytes
  as possible are written.  The current position is then saved to 
  curHTTP.callbackPos and the file is closed.  On subsequent calls, 
  reading begins at the saved location and continues.  Once the end of
  the input file is reached, curHTTP.callbackPos is set back to 0 to 
  indicate completion.

  Precondition:
  None

  Parameters:
  cFile - the name of the file to be sent

  Returns:
    None
    
  Remarks:
  Users should not call this function directly, but should instead add
  dynamic variables in the form of ~inc:filename.ext~ in their HTML code
  to include (for example) the file "filename.ext" at that specified
  location.  The MPFS2 Generator utility will handle the rest.
  ***************************************************************************/
// void HTTPIncFile(ROM BYTE* cFile)
// {
// #ifdef STACK_USE_MDD

//   FILE_HANDLE fp;
//   static DWORD availbleTcpBuffSize,len,numBytes;
//   static BYTE lock=0;
  
//   if((fp = FileOpenROM((const char *)cFile, "r")) == INVALID_FILE_HANDLE)
//   {// File not found, so abort
//       curHTTP.callbackPos = 0x00;
//     return;
//   }
//   else
//   {// The file opened successfully, so seek the file
//     FileSeek(fp, ((DWORD_VAL*)&curHTTP.callbackPos)->w[1], FILE_SEEK_FORWARD);
//     if(lock == 0)
//     {
//       numBytes=(fp->size);
//       lock=1;
//     }
//   }   

//   availbleTcpBuffSize = TCPIsPutReady(sktHTTP);

//   if(availbleTcpBuffSize == 0)
//   {
//      // Save the new address and close the file
//     ((DWORD_VAL*)&curHTTP.callbackPos)->w[1] = FileTell(fp);

     
//     FileClose(fp);
//     EndOfCallBackFileFlag=FALSE;
//     return;
//   }
  
//   if(availbleTcpBuffSize >= 64)
//   {
//     if(numBytes <= 64)
//     {
//       len=FSfread(incDataBuffer, numBytes, 1, fp);
//       TCPPutArray(sktHTTP, incDataBuffer, numBytes);
//       numBytes=0;
//     } 
//     else
//     { 
//       len=FSfread(incDataBuffer, 64, 1, fp);
//       TCPPutArray(sktHTTP, incDataBuffer, 64);
//       numBytes -=64;
//     }
//   }
//   else //if(availbleTcpBuffSize != 0)
//   { 
//     if(numBytes <= availbleTcpBuffSize)
//     {
//       len=FSfread(incDataBuffer, numBytes, 1, fp);
//       TCPPutArray(sktHTTP, incDataBuffer, numBytes);
//       numBytes=0;
//     } 
//     else
//     {
//       len=FSfread(incDataBuffer, availbleTcpBuffSize, 1, fp);
//       TCPPutArray(sktHTTP, incDataBuffer, availbleTcpBuffSize);
//       numBytes -=availbleTcpBuffSize;
//     }
//   }
//   if(numBytes == 0)
//   {// If no bytes were read, an EOF was reached
//     FileClose(fp);
//         curHTTP.callbackPos = 0x00;
//     EndOfCallBackFileFlag=TRUE;
//     lock=0;
//     return;
//   }

//    // Save the new address and close the file
//   ((DWORD_VAL*)&curHTTP.callbackPos)->w[1] = FileTell(fp);
//   FileClose(fp);
//   EndOfCallBackFileFlag=FALSE;

// #else

//   WORD wCount, wLen;
//   BYTE data[64];
//   MPFS_HANDLE fp;
  
//   // Check if this is a first round call
//   if(curHTTP.callbackPos == 0x00u)
//   {// On initial call, open the file and save its ID
//     fp = MPFSOpenROM(cFile);
//     if(fp == MPFS_INVALID_HANDLE)
//     {// File not found, so abort
//       return;
//     }
//     ((DWORD_VAL*)&curHTTP.callbackPos)->w[0] = MPFSGetID(fp);
//   }
//   else
//   {// The file was already opened, so load up its ID and seek
//     fp = MPFSOpenID(((DWORD_VAL*)&curHTTP.callbackPos)->w[0]);
//     if(fp == MPFS_INVALID_HANDLE)
//     {// No file handles available, so wait for now
//       return;
//     }
//     MPFSSeek(fp, ((DWORD_VAL*)&curHTTP.callbackPos)->w[1], MPFS_SEEK_FORWARD);
//   }
  
//   // Get/put as many bytes as possible
//   wCount = TCPIsPutReady(sktHTTP);
//   while(wCount > 0u)
//   {
//     wLen = MPFSGetArray(fp, data, mMIN(wCount, 64u));
//     if(wLen == 0u)
//     {// If no bytes were read, an EOF was reached
//       MPFSClose(fp);
//       curHTTP.callbackPos = 0x00;
//       return;
//     }
//     else
//     {// Write the bytes to the socket
//       TCPPutArray(sktHTTP, data, wLen);
//       wCount -= wLen;
//     }
//   }
  
//   // Save the new address and close the file
//   ((DWORD_VAL*)&curHTTP.callbackPos)->w[1] = MPFSTell(fp);
//   MPFSClose(fp);
  
//   return;
// #endif

// }


// static FILE_HANDLE FileOpenIndex(FILE_HANDLE hFile, BYTE * fileName)
// {
//     #if defined STACK_USE_MPFS2
//         if(MPFSGetFlags(hFile) & MPFS2_FLAG_HASINDEX)
//         {
//         return MPFSOpenID(MPFSGetID(hFile) + 1);
//         }

//     #elif defined STACK_USE_MDD 
//         SearchRec rec;
//         unsigned char attributes = ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN;;
//         int strLen;
        
//         strLen = strlen((const char *)fileName);
//         if(strLen > 100 - 4)
//             return INVALID_FILE_HANDLE; //avoid buffer overflow

//     fileName[strLen] = '\0';
//         if(!FindFirst((const char *)fileName,(unsigned int) attributes, &rec))
//             return FileOpen((const char *)fileName, "r");
//     #endif
//     return INVALID_FILE_HANDLE;
// }

// static WORD FileGetFlags(FILE_HANDLE hFile)
// {
//     #if defined STACK_USE_MPFS2
//         return MPFSGetFlags(hFile);
//     #elif defined STACK_USE_MDD 
//         return 0;//not supported.
//     #endif
// }

//#endif
