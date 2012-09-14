#include <http_server/module.h>
#include <tcpip/wifi.h>

MIDDLEWARE_RESULT Middleware_Utilities(HTTP_SERVER_CONNECTION *connection)
{
  BOOL isDone;
  BYTE *utilName;
  HTTP_SERVER_REQUEST *req;
  HTTP_SERVER_RESPONSE *res;

  // Keep track of the state for each connection locally
  static enum
  {
    SM_START = 0u,
    SM_START_SCAN,

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
        utilName = strstr(req->url, "/utilities/");
        if (utilName == req->url)
        {
          utilName += 11;
          // This is a utility call.  Figure out what utility we are calling
          if(*utilName)
          {
            if(!stricmppgm2ram(utilName, (ROM void*)"networkscan"))
              smStateTracker[connection->ID] = SM_START_SCAN;
            else
            {
              return MIDDLEWARE_DONE;
            }
          }
          else
            return MIDDLEWARE_DONE;
        }
        else
        {
          // This middleware can't handle the call, move on
          return MIDDLEWARE_DONE;
        }

        isDone = FALSE;
        break;

      case SM_START_SCAN:
        // Just start the scan and return
        WF_Scan(WF_SCAN_ALL);
        WIFI_SCAN_ResultCount = 0;
        TCPAdjustFIFOSize(connection->socket, 1, 0, TCP_ADJUST_GIVE_REST_TO_TX);

        ServerResponseWriteHead(connection, HTTP_OK);
        ServerResponseSetSupportedHeader(connection, HEADER_CACHE_CONTROL, "no-cache");
        TCPPutROMString(connection->socket, HTTP_CRLF);
        smStateTracker[connection->ID] = SM_START;
        ServerResponseEnd(connection, NULL);
        return MIDDLEWARE_DONE;
        break;

    }
  } while(!isDone);
}