#include <http_server/module.h>
#include <userconfig.h>
#include <TCPIP Stack/WFApi.h>
#include <json/module.h>
#include <tcpip/wifi.h>

MIDDLEWARE_RESULT Middleware_Networks(HTTP_SERVER_CONNECTION *connection)
{
  BOOL isDone;
  BYTE *resource;
  HTTP_SERVER_REQUEST *req;
  HTTP_SERVER_RESPONSE *res;


  // Keep track of the state for each connection locally
  static enum
  {
    SM_START = 0u,
    SM_GET_INDEX,
    SM_SERVE_INDEX

  }smStateTracker[MAX_HTTP_CONNECTIONS];

  req = &connection->req;
  res = &connection->resp;

  do
  {
    isDone = TRUE;

    switch(smStateTracker[connection->ID])
    {
      case SM_START:
        // Is this a Utility call
        resource = strstr(req->url, "/networks");
        if (resource == req->url)
        {
          resource += 9;
          if(*resource)
          {
          }
          else
          {
            // Base index call.  Don't care about method, just return the networks
            TCPAdjustFIFOSize(connection->socket, 1, 0, TCP_ADJUST_GIVE_REST_TO_TX);
            ServerResponseWriteHead(connection, HTTP_OK);
            ServerResponseSetSupportedHeader(connection, HEADER_CACHE_CONTROL, "no-cache");
            ServerResponseSetSupportedHeader(connection, HEADER_CONTENT_TYPE, "application/json");
            TCPPutROMString(connection->socket, HTTP_CRLF);
            //ServerResponseEnd(connection, "This is the connection information.");
            //return MIDDLEWARE_DONE;
            smStateTracker[connection->ID] = SM_GET_INDEX;
          }
        }
        else
        {
          // This middleware can't handle the call, move on
          smStateTracker[connection->ID] = SM_START;
          return MIDDLEWARE_DONE;
        }

        isDone = FALSE;
        break;


      case SM_GET_INDEX:
        // Get the JSON for the connections and then loop through calls to return it
        connection->genericMemoryPointer = (BYTE*)WIFI_ScanResultsToJSON(WIFI_SCAN_ResultCount);
        connection->sendPointer = connection->genericMemoryPointer;

        smStateTracker[connection->ID] = SM_SERVE_INDEX;
        isDone = FALSE;
        //return MIDDLEWARE_PROCESSING;
        break;

      case SM_SERVE_INDEX:
        if(*(connection->sendPointer))
        {
          connection->sendPointer = TCPPutString(connection->socket, connection->sendPointer);
          return MIDDLEWARE_PROCESSING;
        }
        else
        {
          // Done transmitting
          free(connection->genericMemoryPointer);
          smStateTracker[connection->ID] = SM_START;
          ServerResponseEnd(connection, NULL);
          return MIDDLEWARE_DONE;
        }

        break;
    }
  } while(!isDone);
}