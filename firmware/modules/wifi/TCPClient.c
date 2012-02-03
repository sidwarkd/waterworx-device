#define __TCPCLIENT_C

//#include <userconfig.h>
//#include "TCPIPConfig.h"
//#include <crystalfontz/module.h>


//#include "TCPIP Stack/TCPIP.h"
#include <wifi/module.h>

// Defines the server to be accessed for this application
static BYTE ServerName[] =	"hardlysoftware.com";

// Defines the port to be accessed for this application
static WORD ServerPort = 80;

// Defines the URL to be requested by this HTTP client
static ROM BYTE RemoteURL[] = "/";

void ProcessTCPRequests(void)
{
	WORD				i;
	WORD				w;
	static BYTE			buffer[MAX_RESPONSE_SIZE];
	BYTE				vBuffer[32];
	static WORD offset = 0;
	BYTE *server;
	static DWORD		Timer;
	static TCP_SOCKET	MySocket = INVALID_SOCKET;
	static enum _TCPState
	{
		SM_HOME = 0,
		SM_SOCKET_OBTAINED,
		SM_PROCESS_RESPONSE,
		SM_DISCONNECT,
		SM_PARSE_RESPONSE,
		SM_PERFORM_CALLBACK,
		SM_DONE
		
	} TCPState = SM_DONE;

	static HttpResponse Response;

	switch(TCPState)
	{
		case SM_HOME:
			// Connect a socket to the remote TCP server
			server = GetHeaderValue("Host", CurrentPacket->request.headers);
			MySocket = TCPOpen((DWORD)server, TCP_OPEN_RAM_HOST, CurrentPacket->request.port, TCP_PURPOSE_GENERIC_TCP_CLIENT);
			
			// Abort operation if no TCP socket of type TCP_PURPOSE_GENERIC_TCP_CLIENT is available
			// If this ever happens, you need to go add one to TCPIPConfig.h
			if(MySocket == INVALID_SOCKET)
				break;

			TCPState++;
			Timer = TickGet();
			break;

		case SM_SOCKET_OBTAINED:
			// Wait for the remote server to accept our connection request
			if(!TCPIsConnected(MySocket))
			{
				// Time out if too much time is spent in this state
				if(TickGet()-Timer > 5*TICK_SECOND)
				{
					// Close the socket so it can be used by other modules
					TCPDisconnect(MySocket);
					MySocket = INVALID_SOCKET;
					TCPState--;
				}
				break;
			}

			Timer = TickGet();

			// Make certain the socket can be written to
			if(TCPIsPutReady(MySocket) < 125u)
				break;
			
			// Generate the packet to send
			GenerateRequestPacket(MySocket, &(CurrentPacket->request));

			// Send the packet
			TCPFlush(MySocket);
			TCPState++;
			break;

		case SM_PROCESS_RESPONSE:
			// Check to see if the remote node has disconnected from us or sent us any application data
			if(!TCPIsConnected(MySocket))
			{
				TCPState = SM_DISCONNECT;
				// Do not break;  We might still have data in the TCP RX FIFO waiting for us
			}
	
			// Get count of RX bytes waiting
			w = TCPIsGetReady(MySocket);	

			i = sizeof(vBuffer);
			while(w)
			{
				if(w < i)
				{
					i = w;
				}
				w -= TCPGetArray(MySocket, vBuffer, i);

				memcpy(buffer + offset, vBuffer, sizeof(vBuffer));
				offset += sizeof(vBuffer);

				// putsUART is a blocking call which will slow down the rest of the stack 
				// if we shovel the whole TCP RX FIFO into the serial port all at once.  
				// Therefore, let's break out after only one chunk most of the time.  The 
				// only exception is when the remote node disconncets from us and we need to 
				// use up all the data before changing states.
				if(TCPState == SM_PROCESS_RESPONSE)
					break;
			}

			//TCPState = SM_DISCONNECT;

			break;
	
		case SM_DISCONNECT:
			// Close the socket so it can be used by other modules
			// For this application, we wish to stay connected, but this state will still get entered if the remote server decides to disconnect
			TCPDisconnect(MySocket);
			MySocket = INVALID_SOCKET;
			TCPState = SM_PARSE_RESPONSE;
			break;
	
		case SM_PARSE_RESPONSE:
			buffer[offset + 1] = '\0';
			ParseHttpResponsePacket(&buffer[0], &Response);
			TCPState = SM_PERFORM_CALLBACK;
			break;

		case SM_PERFORM_CALLBACK:
			// Call the callback function to perform processing on the response
			if(CurrentPacket->callback)
			{
				CurrentPacket->callback(&Response);
			}

			CurrentPacket = NULL;
			TCPState = SM_DONE;
			offset = 0;
			break;

		case SM_DONE:
			// Do nothing until there is a pending request
			if(CurrentPacket != NULL)
			{
				TCPState = SM_HOME;
			}
			break;
	}
}

BYTE* GetHeaderValue(CHAR *key, HeaderItem *headers)
{
	UINT8 i = 0;
	for(i = 0; i < MAX_HEADERS; i++)
	{
		HeaderItem *header = headers + i;
		if(strcmp(header->name, key) == 0)
			return header->value;
	}

	return NULL;
}

static void GenerateRequestPacket(TCP_SOCKET socket, HttpRequest *request)
{
	UINT8 i = 0;
	CHAR statusline[MAX_STATUS_LINE_LENGTH];

	// Consturct the status line
	TCPPutString(socket, (BYTE*)request->method);
	TCPPutString(socket, (BYTE*)" ");
	TCPPutString(socket, (BYTE*)request->url);
	TCPPutString(socket, (BYTE*)" HTTP/");
	TCPPutString(socket, (BYTE*)request->http_version);
	TCPPutString(socket, (BYTE*)PACKET_NEWLINE);

	// Construct the headers
	for(i = 0; i < MAX_HEADERS; i++)
	{
		HeaderItem *header = request->headers + i;
		if(*(header->name))
		{
			TCPPutString(socket, (BYTE*)header->name);
			TCPPutString(socket, (BYTE*)": ");
			TCPPutString(socket, (BYTE*)header->value);
			TCPPutString(socket, (BYTE*)PACKET_NEWLINE);
		}
	}

	// Append the body
	TCPPutString(socket, (BYTE*)PACKET_NEWLINE);

	if(request->body)
		TCPPutString(socket, (BYTE*)request->body);
}

static void ParseHttpResponsePacket(BYTE *buffer, HttpResponse *response)
{
	CHAR *token;

	token = strtok((CHAR*)buffer, " ");
	token = strtok(NULL, " ");
	response->status_code = (WORD)atoi(token);
}