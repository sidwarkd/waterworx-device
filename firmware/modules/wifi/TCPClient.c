#define __TCPCLIENT_C

#include <wifi/module.h>

void ProcessTCPRequests(void)
{
	WORD bytesToRead;
	WORD numRXBytesReady;
	BYTE vBuffer[32];
	BYTE *server;
	UINT16 i;

	static BYTE	buffer[MAX_RESPONSE_SIZE];
	static BYTE	txPacket[1024];
	static WORD offset = 0;
	static BYTE *txPos;
	static DWORD Timer;
	static TCP_SOCKET	MySocket = INVALID_SOCKET;

	static enum _TCPState
	{
		SM_HOME = 0,
		SM_SOCKET_OBTAINED,
		SM_SEND_REQUEST,
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

			// Generate the packet to send
			GenerateRequestPacket(&(CurrentPacket->request), &txPacket[0]);

			txPos = &txPacket[0];
			TCPState++;
			break;

		case SM_SEND_REQUEST:
			if(*txPos != '\0')
			{
				txPos = TCPPutString(MySocket, txPos);
			}
			else
			{
				TCPFlush(MySocket);
				txPos = NULL;
				memset(txPacket, 0, sizeof(txPacket));
				TCPState++;
			}
			break;

		case SM_PROCESS_RESPONSE:
			// Check to see if the remote node has disconnected from us or sent us any application data
			if(!TCPIsConnected(MySocket))
			{
				TCPState = SM_DISCONNECT;
				// Do not break;  We might still have data in the TCP RX FIFO waiting for us
			}
	
			// Get count of RX bytes waiting
			numRXBytesReady = TCPIsGetReady(MySocket);	

			bytesToRead = sizeof(vBuffer);
			while(numRXBytesReady)
			{
				if(numRXBytesReady < bytesToRead)
				{
					bytesToRead = numRXBytesReady;
				}
				
				numRXBytesReady -= TCPGetArray(MySocket, vBuffer, bytesToRead);

				// TODO: Assumes call above actually read bytesToRead number of bytes. Maybe change this
				// memcpy to copy the return number from TCPGetArray
				memcpy(buffer + offset, vBuffer, bytesToRead);
				offset += bytesToRead;
 
				// Therefore, let's break out after only one chunk most of the time.  The 
				// only exception is when the remote node disconncets from us and we need to 
				// use up all the data before changing states.
				if(TCPState == SM_PROCESS_RESPONSE)
					break;
			}

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
			// Clear out the response
			Response.status_code = 0;
			Response.body[0] = '\0';
			TCPState = SM_DONE;
			offset = 0;
			break;

		case SM_DONE:
			// Do nothing until there is a pending request
			for(i = 0; i < ARRAY_SIZE(Response.body); i++)
			{
				Response.body[i] = '\0';
			}
			
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

static void GenerateRequestPacket(HttpRequest *request, BYTE *packet)
{
	UINT8 i = 0;
	CHAR statusline[MAX_STATUS_LINE_LENGTH];

	// Consturct the status line
	strcat(packet, (BYTE*)request->method);
	strcat(packet, (BYTE*)" ");
	strcat(packet, (BYTE*)request->url);
	strcat(packet, (BYTE*)" HTTP/");
	strcat(packet, (BYTE*)request->http_version);
	strcat(packet, (BYTE*)PACKET_NEWLINE);


	// Construct the headers
	for(i = 0; i < MAX_HEADERS; i++)
	{
		HeaderItem *header = request->headers + i;
		if(*(header->name))
		{
			strcat(packet, (BYTE*)header->name);
			strcat(packet, (BYTE*)": ");
			strcat(packet, (BYTE*)header->value);
			strcat(packet, (BYTE*)PACKET_NEWLINE);
		}
	}

	// Append the body
	strcat(packet, (BYTE*)PACKET_NEWLINE);

	if(request->body)
	{
		strcat(packet, (BYTE*)request->body);
		//strcat(packet, (BYTE*)"{\"did\":\"123456\",\"name\":\"prototype\"}");
	}
}

static void ParseHttpResponsePacket(BYTE *buffer, HttpResponse *response)
{
	CHAR *token;
	CHAR *bodyptr;
	UINT8 i = 0;

	// Before we mess with the buffer with strtok let's find the body
	bodyptr = strstr((CHAR*)buffer, "\r\n\r\n");

	token = strtok((CHAR*)buffer, " ");
	token = strtok(NULL, " ");
	response->status_code = (WORD)atoi(token);

	// Take as many headers as we can
	// TODO: Add header parsing when needed

	if(bodyptr && (bodyptr + 4))
	{
		strcpy(response->body, bodyptr + 4);
	}
}