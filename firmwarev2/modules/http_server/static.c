#include <http_server/module.h>

BYTE sendDataBuffer[512];

static BOOL HTTPServeStaticAsset(HTTP_SERVER_CONNECTION *activeConnection);

// Determine if this request is for a static asset and if we can service it

MIDDLEWARE_RESULT Middleware_Static(HTTP_SERVER_CONNECTION *connection)
{
    BYTE *queryStringPos;
  BYTE *ext;
  CHAR filename[64];
  HTTP_SERVER_REQUEST *req;
  HTTP_SERVER_RESPONSE *res;

  req = &connection->req;
  res = &connection->resp;

  switch(connection->middlewareState)
  {
    case STATIC_MIDDLEWARE_START:
      queryStringPos = strchr(req->url, '?');
      ext = strchr(req->url, '.');

      // There is a period that must be a file extension because there is
      // no query string that might contain periods in the data.  This is
      // a simple indicator of a static asset.
      if(ext != NULL && queryStringPos == NULL)
      {
        // Make sure the file exists. Add the root dir to the file
        sprintf(filename, "public%s", req->url);
        connection->file = FATFS_fopen(filename, "r");
        if(connection->file == NULL)
        {
          mLED_Red_Toggle();
          SetResponseStatus(res, HTTP_NOT_FOUND);
          connection->state = SM_CONNECTION_HANDLE_ERROR;
          connection->middlewareState = 0x00;
          return MIDDLEWARE_DONE;
        }
            
        // Find the extension in the filename
        ext++;
        for(res->returnType = HTTP_TXT; res->returnType < HTTP_UNKNOWN; res->returnType++)
         if(!stricmppgm2ram(ext, (ROM void*)httpFileExtensions[res->returnType]))
           break;


        TCPAdjustFIFOSize(connection->socket, 1, 0, TCP_ADJUST_GIVE_REST_TO_TX);
            
        // Send top response line with status
        TCPPutROMString(connection->socket, (ROM BYTE*)HTTPResponseChunks[res->status]); 

        // Output the content type, if known
        if(res->returnType != HTTP_UNKNOWN)
        {
          TCPPutROMString(connection->socket, (ROM BYTE*)"Content-Type: ");
          TCPPutROMString(connection->socket, (ROM BYTE*)httpContentTypes[res->returnType]);
          TCPPutROMString(connection->socket, HTTP_CRLF);
        }

        ServerResponseSetSupportedHeader(connection, HEADER_CACHE_CONTROL, "max-age=600");
            
        // Terminate the headers
        TCPPutROMString(connection->socket, HTTP_CRLF);
        TCPFlush(connection->socket);
        connection->middlewareState = STATIC_MIDDLEWARE_SERVING_ASSET;

      }
      else
      {
        // Not a static asset request so move on
        connection->middlewareState = 0x00;
        return MIDDLEWARE_DONE;
      }
      //break;

    case STATIC_MIDDLEWARE_SERVING_ASSET:
      if(HTTPServeStaticAsset(connection) == FALSE)
      {
        return MIDDLEWARE_PROCESSING;
      }
      else
      {
        connection->middlewareState = STATIC_MIDDLEWARE_DONE;
      }
      //break;

    case STATIC_MIDDLEWARE_DONE:
      connection->middlewareState = 0x00;
      return MIDDLEWARE_DONE;
      break;

    default:
      connection->middlewareState = 0x00;
      return MIDDLEWARE_DONE;
      break;
  } // end switch on middleware state
}

static BOOL HTTPServeStaticAsset(HTTP_SERVER_CONNECTION *activeConnection)
{
  DWORD numBytes;
  DWORD availbleTcpBuffSize, len;

  // The following sets up separate tracking of state for each
  // possible connection.  C should initialize all to the IDLE
  // state
  static enum
  {
    SM_IDLE = 0u,
    SM_SERVE_TEXT_DATA

  }smStateTracker[MAX_HTTP_CONNECTIONS];

  switch(smStateTracker[activeConnection->connectionID])
  {

    case SM_IDLE:
      activeConnection->resp.numBytesLeftToServe = FATFS_fsize(activeConnection->file);

    case SM_SERVE_TEXT_DATA:

      memset(sendDataBuffer, 0, sizeof(sendDataBuffer));

      availbleTcpBuffSize = TCPIsPutReady(activeConnection->socket);
      
      if(availbleTcpBuffSize >= 512)
      {
        if(activeConnection->resp.numBytesLeftToServe >= 512)
        {
          len=FATFS_fread(sendDataBuffer, 1, 512, activeConnection->file);
          TCPPutArray(activeConnection->socket, sendDataBuffer, len);
          activeConnection->resp.numBytesLeftToServe -= len;
        }
        else
        {
          len=FATFS_fread(sendDataBuffer, 1, activeConnection->resp.numBytesLeftToServe, activeConnection->file);
          TCPPutArray(activeConnection->socket, sendDataBuffer, len);
          activeConnection->resp.numBytesLeftToServe = 0;

        }
      }
      else if(availbleTcpBuffSize != 0)
      {
        if(activeConnection->resp.numBytesLeftToServe >= availbleTcpBuffSize)
        {
          len=FATFS_fread(sendDataBuffer, 1, availbleTcpBuffSize, activeConnection->file);
          TCPPutArray(activeConnection->socket, sendDataBuffer, len);
          activeConnection->resp.numBytesLeftToServe -= len;
        }
        else 
        {
          len=FATFS_fread(sendDataBuffer, 1, activeConnection->resp.numBytesLeftToServe, activeConnection->file);
          TCPPutArray(activeConnection->socket, sendDataBuffer, activeConnection->resp.numBytesLeftToServe);
          activeConnection->resp.numBytesLeftToServe = 0;
          
        }
      }
      if(activeConnection->resp.numBytesLeftToServe <= 100)
      {
        activeConnection->resp.numBytesLeftToServe = activeConnection->resp.numBytesLeftToServe;
      }
      if(activeConnection->resp.numBytesLeftToServe == 0)
      {
        TCPFlush(activeConnection->socket);

        FATFS_fclose(activeConnection->file);

        smStateTracker[activeConnection->connectionID] = SM_IDLE;
        return TRUE;
      }

      TCPFlush(activeConnection->socket);
      break;
        
  }

  if(FATFS_feof(activeConnection->file) || activeConnection->resp.numBytesLeftToServe == 0)
  {
    TCPFlush(activeConnection->socket);
    
    FATFS_fclose(activeConnection->file);
            
    smStateTracker[activeConnection->connectionID] = SM_IDLE;
    return TRUE;
  }

  return FALSE;
}