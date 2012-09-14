#include "TCPIP Stack/TCPIP.h"

// Static function definitions
//void HTTPLoadConn(BYTE hHTTP);
static void ServiceHttpConnection(HTTP_SERVER_CONNECTION *connection);
static void InitializeServerConnection(HTTP_SERVER_CONNECTION *connection);
static HTTP_METHOD GetHTTPMethodFromServerRequest(HTTP_SERVER_CONNECTION *connection);
static HTTP_STATUS GetRequestURI(HTTP_SERVER_CONNECTION *connection);
static void AddHeaderToRequest(HTTP_SERVER_CONNECTION *connection, CHAR *headerLine);

ROM BYTE HTTP_CRLF[] = "\r\n"; // New line sequence
HTTP_SERVER_CONNECTION httpConnections[MAX_HTTP_CONNECTIONS];
BYTE activeConnectionID;
MIDDLEWARE_MODULE middlewareModules[MAX_MIDDLEWARE_MODULES];

ROM char * ROM HTTPResponseChunks[] =
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

// Header strings for which we'd like to parse
  ROM char * ROM HTTPSupportedHeaders[] =
  {
    "Cookie:",
    "Authorization: ",
    "Content-Length: ",
    "Content-Type: ",
    "Connection: ",
    "Cache-Control: "
  };

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

// This function must be called HTTPInit so it can be properly called by the stack
void HTTPInit(void)
{
  UINT8 i = 0;
  for(i = 0; i < MAX_HTTP_CONNECTIONS; i++)
  {
    httpConnections[i].state = SM_CONNECTION_IDLE;
    httpConnections[i].socket = TCPOpen(0, TCP_OPEN_SERVER, HTTP_PORT, TCP_PURPOSE_HTTP_SERVER);
    #if defined(STACK_USE_SSL_SERVER)
    TCPAddSSLListener(httpConnections[i].socket, HTTPS_PORT);
    #endif
    httpConnections[i].connectionID = i;
  }

  // Blank out all of the middleware
  for(i = 0; i < MAX_MIDDLEWARE_MODULES; i++)
  {
    middlewareModules[i].next = NULL;
    middlewareModules[i].process = NULL;
  }

  // Configure what middleware modules you want to run here
  middlewareModules[0].process = Middleware_Static;
}

void HTTPServer(void)
{
  BYTE connectionIndex;
  HTTP_SERVER_CONNECTION *activeConnection;

  for(connectionIndex = 0; connectionIndex < MAX_HTTP_CONNECTIONS; connectionIndex++)
  {
    activeConnection = &httpConnections[connectionIndex];
    if(activeConnection->socket == INVALID_SOCKET)
      continue;
    
    // If a socket is disconnected at any time 
    // forget about it and return to idle state.
    // Must do this here, otherwise we will wait until a new
    // connection arrives, which causes problems with Linux and with SSL
    if(TCPWasReset(activeConnection->socket))
    {
      //HTTPLoadConn(conn);
      activeConnection->state = SM_CONNECTION_IDLE;

      // Make sure any opened files are closed
      if(activeConnection->file != NULL)
      {
        FATFS_fclose(activeConnection->file);
        activeConnection->file = NULL;
      }

      // Adjust FIFO sizes to half and half.  Default state must remain
      // here so that SSL handshakes, if required, can proceed
      TCPAdjustFIFOSize(activeConnection->socket, 1, 0, TCP_ADJUST_PRESERVE_RX);
    }
    
    // Determine if this connection is eligible for processing
    if(activeConnection->state != SM_CONNECTION_IDLE || TCPIsGetReady(activeConnection->socket))
    {
      //HTTPLoadConn(conn);
      //HTTPProcess();
      ServiceHttpConnection(activeConnection);
    }
  }
}

/*static void HTTPLoadConn(BYTE hHTTP)
{
  // Return if already loaded
  if(hHTTP == activeConnectionID)
    return;
    
  // Before we switch let's flush the existing connection
  TCPFlush(activeSocket);
  activeConnectionID = hHTTP;
}*/

static void ServiceHttpConnection(HTTP_SERVER_CONNECTION *connection)
{
  BOOL isDone;
  WORD lenA;

  do
  {
    isDone = TRUE;

    switch(connection->state)
    {
      case SM_CONNECTION_IDLE:
        // Is there any data waiting on this connection's socket
        // We only break if data is not ready.  If there is data
        // we'll immediately fall through to the next state
        if(TCPIsGetReady(connection->socket))
        {
            InitializeServerConnection(connection);
            
            connection->state = SM_CONNECTION_PARSE_REQUEST;

            // Adjust the TCP FIFOs for optimal reception of 
            // the next HTTP request from the browser
            TCPAdjustFIFOSize(connection->socket, 1, 0, TCP_ADJUST_PRESERVE_RX | TCP_ADJUST_GIVE_REST_TO_RX);
        }
        else
          break;
  // ==========================================================================================================      
  // ==========================================================================================================      
      case SM_CONNECTION_PARSE_REQUEST:
        // In this state we will extract data from the request and
        // populate the req member of our connection to be used as necessary

        // Verify the entire first line is in the FIFO
        if(TCPFind(connection->socket, '\n', 0, FALSE) == 0xffff)
        {// First line isn't here yet
          if(TCPGetRxFIFOFree(connection->socket) == 0u)
          {// If the FIFO is full, we overflowed
            SetResponseStatus(&connection->resp, HTTP_OVERFLOW);
            connection->state = SM_CONNECTION_HANDLE_ERROR;
            isDone = FALSE;
          }
          if((LONG)(TickGet() - connection->wdTimer) > (LONG)0)
          {// A timeout has occurred
            TCPDisconnect(connection->socket);
            connection->state = SM_CONNECTION_DISCONNECT;
            isDone = FALSE;
          }
          // Break here so we can loop back through to see if the first line
          // has completely arrived
          break;
        }

        // Reset the watchdog timer
        connection->wdTimer = TickGet() + HTTP_TIMEOUT*TICK_SECOND;

        // Determine the request method
        connection->req.method = GetHTTPMethodFromServerRequest(connection);
        if(connection->req.method == HTTP_UNKNOWN_METHOD)
        {
          SetResponseStatus(&connection->resp, HTTP_NOT_IMPLEMENTED);
          connection->state = SM_CONNECTION_HANDLE_ERROR;
          isDone = FALSE;
          // Break here to go through the switch again and straight to
          // the error handling
          break;
        }

        connection->resp.status = GetRequestURI(connection);
        if(connection->resp.status != HTTP_OK)
        {
          connection->state = SM_CONNECTION_HANDLE_ERROR;
          isDone = FALSE;
          break;
        }

        // Move to parsing the headers
        connection->state = SM_CONNECTION_PARSE_HEADERS;
        
        // No break, continue to parsing headers

        break;
  // ==========================================================================================================      
  // After the SM_CONNECTION_PARSE_HEADERS state the req stuct of the
  // connection will be fully populated        
  // ==========================================================================================================      
      case SM_CONNECTION_PARSE_HEADERS:
        // Loop over all the headers
        while(1)
        {
          // Make sure entire line is in the FIFO
          lenA = TCPFind(connection->socket, '\n', 0, FALSE);
          if(lenA == 0xffff)
          {// If not, make sure we can receive more data
            if(TCPGetRxFIFOFree(connection->socket) == 0u)
            {// Overflow
              SetResponseStatus(&connection->resp, HTTP_OVERFLOW);
              connection->state = SM_CONNECTION_HANDLE_ERROR;
              isDone = FALSE;
            }
            if((LONG)(TickGet() - connection->wdTimer) > (LONG)0)
            {// A timeout has occured
              TCPDisconnect(connection->socket);
              connection->state = SM_CONNECTION_DISCONNECT;
              isDone = FALSE;
            }
            break;
          }
          
          // Reset the watchdog timer
          connection->wdTimer = TickGet() + HTTP_TIMEOUT*TICK_SECOND;
          
          // If a CRLF is immediate, then headers are done
          if(lenA == 1u)
          {
            // Remove the CRLF and move to next state
            TCPGetArray(connection->socket, NULL, 2);
            connection->state = SM_CONNECTION_EXECUTE_MIDDLEWARE;
            isDone = FALSE;
            break;
          }

          // Read in the entire line and send it off for parsing
          if(lenA > sizeof(connection->data))
          {
            TCPGetArray(connection->socket, NULL, lenA + 1);
            continue;
          }

          TCPGetArray(connection->socket, connection->data, lenA + 1);
          connection->data[lenA-1] = '\0';
          
          AddHeaderToRequest(connection, (CHAR*)connection->data);

        } // while loop over headers

        break;
  // ==========================================================================================================      
  // ==========================================================================================================      
      case SM_CONNECTION_EXECUTE_MIDDLEWARE:
        if(connection->activeMiddleware != NULL && connection->activeMiddleware->process != NULL)
        {
          switch (connection->activeMiddleware->process(connection))
          {
            case MIDDLEWARE_NEED_DATA:
              break;
            case MIDDLEWARE_PROCESSING:
              break;
            case MIDDLEWARE_DONE:
              connection->activeMiddleware = connection->activeMiddleware->next;
              isDone = FALSE;
              break;
          }
        }
        else
        {
          // One of the middleware modules has finished the response
          connection->state = SM_CONNECTION_DISCONNECT;
          isDone = FALSE;
        }
        break;
  // ==========================================================================================================      
  // ==========================================================================================================      
      case SM_CONNECTION_HANDLE_ERROR:
        TCPAdjustFIFOSize(connection->socket, 1, 0, TCP_ADJUST_GIVE_REST_TO_TX);
        
        // Send headers
        TCPPutROMString(connection->socket, (ROM BYTE*)HTTPResponseChunks[connection->resp.status]);

        connection->state = SM_CONNECTION_DISCONNECT;
        break;
  // ==========================================================================================================      
  // ==========================================================================================================      
      case SM_CONNECTION_DISCONNECT:
        // Make sure any opened files are closed
        if(connection->file != NULL)
        {
          FATFS_fclose(connection->file);
          connection->file = NULL;
        }

        TCPDisconnect(connection->socket);
        connection->state = SM_CONNECTION_IDLE;
        break;
    } // End switch
  } while (!isDone);
}


void InitializeServerConnection(HTTP_SERVER_CONNECTION *connection)
{
  connection->resp.status = HTTP_OK;
  connection->resp.returnType = HTTP_UNKNOWN;
  //connection->resp.disableCache = FALSE;
  //connection->resp.headersWritten = FALSE;

  connection->req.method = HTTP_GET;
  connection->req.url[0] = '\0';
  connection->req.contentLength = 0;
  
  connection->wdTimer = TickGet() + HTTP_TIMEOUT*TICK_SECOND;
  connection->bytesAvailable = 0xffffffff;
  connection->data[0] = '\0';
  connection->activeMiddleware = &middlewareModules[0];
  connection->middlewareState = 0x00;
}

// ======================================================================================
// ======================================================================================
// HELPER FUNCTIONS
// ======================================================================================
static HTTP_METHOD GetHTTPMethodFromServerRequest(HTTP_SERVER_CONNECTION *connection)
{
  WORD methodNameLength;

  methodNameLength = TCPFind(connection->socket, ' ', 0, FALSE);
  if(methodNameLength > 6u) // 6 to accomodate DELETE
    methodNameLength = 6;

  TCPGetArray(connection->socket, connection->data, methodNameLength+1);

  if(memcmppgm2ram(connection->data, (ROM void*)"GET", 3) == 0)
    return HTTP_GET;
  #if defined(HTTP_USE_POST)
  else if ( memcmppgm2ram(connection->data, (ROM void*)"POST", 4) == 0)
    return HTTP_POST;
  #endif
  else if ( memcmppgm2ram(connection->data, (ROM void*)"PUT", 3) == 0)
    return HTTP_PUT;
  else if ( memcmppgm2ram(connection->data, (ROM void*)"DELETE", 6) == 0)
    return HTTP_DELETE;
  else
  {
    return HTTP_UNKNOWN_METHOD;
  }
}

static HTTP_STATUS GetRequestURI(HTTP_SERVER_CONNECTION *connection)
{
  WORD lenA, lenB;

  // Find end of uri
  lenA = TCPFind(connection->socket, ' ', 0, FALSE);
  
  // If the uri is too long, then reject the request
  if(lenA > HTTP_MAX_DATA_LEN - HTTP_DEFAULT_LEN - 1)
  {
    return HTTP_OVERFLOW;
  }

  // Read in the request uri with query string
  lenB = TCPGetArray(connection->socket, connection->data, lenA);
  connection->data[lenB] = '\0';
  strcpy(connection->req.url, connection->data);


  // Clear the rest of the line
  lenA = TCPFind(connection->socket, '\n', 0, FALSE);
  TCPGetArray(connection->socket, NULL, lenA + 1);
  return HTTP_OK;
}

static void AddHeaderToRequest(HTTP_SERVER_CONNECTION *connection, CHAR *headerLine)
{
  CHAR *token;
  token = strtok(headerLine, ":");
  if(token != NULL)
  {
    if(strcmppgm2ram((char*)token, (ROM char *)"Content-Length") == 0)
    {
      token = strtok(NULL, ":");
      if(token != NULL)
      {
        connection->req.contentLength = atol(token);       
      }
    }
  }
}

// ======================================================================================
// ======================================================================================
// The following are functions that we wire up to our request and response objects
// to make them function in a similar manner to Node.js
// ======================================================================================

void SetResponseStatus(HTTP_SERVER_RESPONSE *resp, HTTP_STATUS status)
{
  resp->status = status;
}

void ServerResponseWriteHead(HTTP_SERVER_RESPONSE *resp, HTTP_STATUS status)
{

}

void ServerResponseSetCustomHeader(CHAR *name, CHAR *value)
{

}

void ServerResponseSetSupportedHeader(HTTP_SERVER_CONNECTION *connection, HEADER_NAME_INDEX index, CHAR *value)
{
  if(index >= HEADER_START && index < HEADER_END)
  {
    TCPPutROMString(connection->socket, HTTPSupportedHeaders[index]);
    TCPPutString(connection->socket, value);
    TCPPutROMString(connection->socket, HTTP_CRLF);
  }
}

void ServerResponseWrite(BYTE *data)
{

}

void ServerResponseEnd(BYTE *data)
{

}


