#ifndef HTTP_SERVER_MODULE_H
#define HTTP_SERVER_MODULE_H

#include <userconfig.h>
#include <base/module.h>
#include <TCPIP Stack/TCPIP.h>

//#include <tcpip/TCPIPConfig.h>
//#include <tcpip/WF_Config.h>

//#include <TCPIP Stack/WFEasyConfig.h>
#include <sdcard/module.h>

// Put compile errors if missing WF pin definitions

/****************************************************************************
  Section:
	Server Configuration Settings
  ***************************************************************************/

#if !defined(HTTP_PORT)
    #define HTTP_PORT               (80u)	// Listening port for HTTP server
#endif
#if !defined(HTTPS_PORT)
    #define HTTPS_PORT				(443u)	// Listening port for HTTPS server (when SSL enabled)
#endif
#if !defined(HTTP_MAX_DATA_LEN)
    #define HTTP_MAX_DATA_LEN		(100u)
#endif
#if !defined(HTTP_MIN_CALLBACK_FREE)
    #define HTTP_MIN_CALLBACK_FREE	(16u)
#endif
#define HTTP_CACHE_LEN			("600")	// Max lifetime (sec) of static responses as string
#define HTTP_TIMEOUT			(45u)	// Max time (sec) to await more data before timing out and disconnecting the socket

// Authentication requires Base64 decoding
#if defined(HTTP_USE_AUTHENTICATION)
#ifndef STACK_USE_BASE64_DECODE
	#define STACK_USE_BASE64_DECODE
#endif
#endif

typedef enum
{
	HTTP_OK = 0u,									// 200 Everything is good
  HTTP_BAD_REQUEST,							// 400 Bad Request will be returned
	HTTP_UNAUTHORIZED,						// 401 Unauthorized will be returned
  HTTP_NOT_FOUND,								// 404 Not Found will be returned
	HTTP_OVERFLOW,								// 414 Request-URI Too Long will be returned
	HTTP_INTERNAL_SERVER_ERROR,		// 500 Internal Server Error will be returned
	HTTP_NOT_IMPLEMENTED,					// 501 Not Implemented (not a GET or POST command)
	HTTP_REDIRECT,								// 302 Redirect will be returned
	HTTP_SSL_REQUIRED							// 403 Forbidden is returned, indicating SSL is required

} HTTP_STATUS;

typedef enum 
{  
	HTTP_GET = 0u,
	HTTP_POST,
	HTTP_PUT,
	HTTP_DELETE,
	HTTP_UNKNOWN_METHOD

} HTTP_METHOD;

typedef enum
{
	HEADER_START = 0u,
	HEADER_COOKIE = 0u,
	HEADER_AUTH,
	HEADER_CONTENT_LENGTH,
	HEADER_CONTENT_TYPE,
	HEADER_CONNECTION,
	HEADER_CACHE_CONTROL,
	HEADER_END

} HEADER_NAME_INDEX;

typedef enum
{
	HTTP_TXT = 0u,		// File is a text document
	HTTP_HTM,					// File is HTML (extension .htm)
	HTTP_HTML,				// File is HTML (extension .html)
	HTTP_CGI,					// File is HTML (extension .cgi)
	HTTP_XML,					// File is XML (extension .xml)
	HTTP_CSS,					// File is stylesheet (extension .css)
	HTTP_GIF,					// File is GIF image (extension .gif)
	HTTP_PNG,					// File is PNG image (extension .png)
	HTTP_JPG,					// File is JPG image (extension .jpg)
	HTTP_JAVA,				// File is java (extension .java)
	HTTP_WAV,					// File is audio (extension .wav)
	HTTP_JS,					// File is javascript (extension .js)
	HTTP_JSON,				// Return data is json
	HTTP_UNKNOWN			// File type is unknown

} HTTP_FILE_TYPE;

typedef enum
{
	MIDDLEWARE_DONE = 0u,	// Finished with procedure
	MIDDLEWARE_NEED_DATA,	// More data needed to continue, call again later
	MIDDLEWARE_PROCESSING		// Waiting for asynchronous process to complete, call again later

} MIDDLEWARE_RESULT;

typedef enum
{
	SM_CONNECTION_IDLE = 0u,					// Socket is idle
	SM_CONNECTION_PARSE_REQUEST,			// Parses the first line for a file name and GET args
	SM_CONNECTION_PARSE_HEADERS,			// Reads and parses headers one at a time
	SM_CONNECTION_EXECUTE_MIDDLEWARE,
	SM_CONNECTION_HANDLE_ERROR,
	SM_CONNECTION_DISCONNECT					// Disconnects the server and closes all files

} CONNECTION_STATE;

typedef struct
{
	HEADER_NAME_INDEX nameID;
	CHAR *value;  // This could point to a ROM string or dynamically generated string

} HTTP_HEADER;

// Patterned after the NodeJS http.ServerRequest object
typedef struct 
{
	HTTP_METHOD method;			// Method used (GET, POST, PUT, DELETE)
	BYTE url[MAX_URL_LEN];	// The url including query string if present
	DWORD contentLength;

} HTTP_SERVER_REQUEST;

typedef struct 
{
	HTTP_STATUS status;
	HTTP_FILE_TYPE returnType;
	DWORD numBytesLeftToServe;

} HTTP_SERVER_RESPONSE;

struct _MIDDLEWARE_MODULE;
struct _HTTP_SERVER_CONNECTION;

typedef struct _MIDDLEWARE_MODULE
{
	MIDDLEWARE_RESULT (*process)(struct _HTTP_SERVER_CONNECTION *connection);

} MIDDLEWARE_MODULE;

typedef struct _HTTP_SERVER_CONNECTION
{
	UINT8 ID;
	HTTP_SERVER_REQUEST req;
	HTTP_SERVER_RESPONSE resp;
	CONNECTION_STATE state;
	TCP_SOCKET socket;
	DWORD wdTimer;
	BYTE data[HTTP_MAX_DATA_LEN];	// General purpose data buffer
	DWORD bytesAvailable;
	FILEHANDLE *file;
	MIDDLEWARE_MODULE *activeMiddleware;
	BYTE middlewareState;
	BYTE *sendPointer;
	BYTE *genericMemoryPointer;  // Use to keep track of heap allocations assiged to a connection

} HTTP_SERVER_CONNECTION;


	// Globals
extern HTTP_SERVER_CONNECTION httpConnections[MAX_HTTP_CONNECTIONS];
extern BYTE activeConnectionID;

extern ROM char * ROM HTTPResponseChunks[];
extern ROM char * ROM HTTPSupportedHeaders[];
extern ROM char * ROM httpContentTypes[HTTP_UNKNOWN+1];
extern ROM char * ROM httpFileExtensions[HTTP_UNKNOWN+1];

#define HTTP_CRLF_LEN 2       // Length of above string
extern ROM BYTE HTTP_CRLF[HTTP_CRLF_LEN];

#define MAX_MIDDLEWARE_MODULES 5
extern MIDDLEWARE_MODULE middlewareModules[MAX_MIDDLEWARE_MODULES];

void SetResponseStatus(HTTP_SERVER_RESPONSE *resp, HTTP_STATUS status);
void ServerResponseWriteHead(HTTP_SERVER_CONNECTION *connection, HTTP_STATUS status);
void ServerResponseSetSupportedHeader(HTTP_SERVER_CONNECTION *connection, HEADER_NAME_INDEX index, CHAR *value);
void ServerResponseSetCustomHeader(HTTP_SERVER_CONNECTION *connection, CHAR *name, CHAR *value);
void ServerResponseWrite(HTTP_SERVER_CONNECTION *connection, BYTE *data);
void ServerResponseEnd(HTTP_SERVER_CONNECTION *connection, BYTE *data);


#define RESERVED_HTTP_MEMORY 0ul

// The following defines are for quick, clean-code access to the connection
// being actively serviced
//#define activeConnection 			(httpConnections[activeConnectionID])
//#define activeConnectionState (httpConnections[activeConnectionID].state)
//#define activeRequest 				(httpConnections[activeConnectionID].request)
//#define activeResponse  			(httpConnections[activeConnectionID].response)

// Middleware Functions
MIDDLEWARE_RESULT Middleware_Static(HTTP_SERVER_CONNECTION *connection);
MIDDLEWARE_RESULT Middleware_Utilities(HTTP_SERVER_CONNECTION *connection);
MIDDLEWARE_RESULT Middleware_Networks(HTTP_SERVER_CONNECTION *connection);


typedef enum 
{
	STATIC_MIDDLEWARE_START = 0u,
	STATIC_MIDDLEWARE_SERVING_ASSET,
	STATIC_MIDDLEWARE_DONE
} STATIC_MIDDLEWARE_STATE;

// HardwareProfile.h
#define GENERATED_BY_TCPIPCONFIG "Version 1.0.4168.28618"

// main.h
#define SaveAppConfig(a)
void ProcessTCPRequests(void);
void DisplayIPValue(IP_ADDR IPVal);

// Core Module Functions
// void WIFI_Initialize(void);
// void WIFI_PerformStackTasks(void);
// void WIFI_PerformGet(CHAR *server, CHAR* url, void (*callback)(HttpResponse *response));
// void WIFI_PerformPost(CHAR *server, CHAR* url, CHAR* body, void (*callback)(HttpResponse *response));

// // Helper Functions
// BYTE* GetHeaderValue(CHAR *key, HeaderItem *headers);
// static void GenerateRequestPacket(HttpRequest *request, BYTE *packet);
// static void ParseHttpResponsePacket(BYTE *buffer, HttpResponse *response);

#endif