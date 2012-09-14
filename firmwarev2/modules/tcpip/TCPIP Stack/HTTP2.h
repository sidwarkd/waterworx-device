/*********************************************************************
 *
 *               HTTP Headers for Microchip TCP/IP Stack
 *
 *********************************************************************
 * FileName:        HTTP2.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
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
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
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
 * Author               Date    Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Nilesh Rajbharti     8/14/01 Original
 * Elliott Wood			6/4/07	Complete rewrite (known as HTTP2)
********************************************************************/

#ifndef __HTTP2_H
#define __HTTP2_H

#include "TCPIP Stack/TCPIP.h"
#include <sdcard/module.h>

#if defined(STACK_USE_HTTP2_SERVER)

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

/****************************************************************************
  Section:
	Commands and Server Responses
  ***************************************************************************/

	//Supported Commands and Server Response Codes
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

/****************************************************************************
  Section:
	HTTP State Definitions
  ***************************************************************************/

	// Basic HTTP Connection State Machine
	typedef enum
	{
		SM_HTTP_IDLE = 0u,					// Socket is idle
		SM_HTTP_PARSE_REQUEST,			// Parses the first line for a file name and GET args
		SM_HTTP_PARSE_HEADERS,			// Reads and parses headers one at a time
		SM_HTTP_AUTHENTICATE,				// Validates the current authorization state
		SM_HTTP_PROCESS_GET,				// Invokes user callback for GET args or cookies
		SM_HTTP_PROCESS_POST,				// Invokes user callback for POSTed data
		SM_HTTP_HANDLE_ERROR,
		SM_HTTP_DISCONNECT					// Disconnects the server and closes all files
	} SM_HTTP2;

	typedef enum 
	{  
		ROUTE_PROCESS_REQUEST = 0u,	// Figure out if it is a static asset or dynamic route
		ROUTE_SERVE_HEADERS,				// Serve up the request-specific headers
		ROUTE_SERVE_BODY,						// Serve up the body if necessary
		ROUTE_DONE									// Finish up route processing
	} HTTP_ROUTE_STATE;


	// Result states for execution callbacks
	typedef enum
	{
		HTTP_IO_DONE = 0u,	// Finished with procedure
		HTTP_IO_NEED_DATA,	// More data needed to continue, call again later
		HTTP_IO_WAITING		// Waiting for asynchronous process to complete, call again later
	} HTTP_IO_RESULT;


	// Result states for HTTPPostReadName and HTTPPostReadValue
	typedef enum
	{
		HTTP_READ_OK = 0u,		// Read was successful
		HTTP_READ_TRUNCATED,	// Buffer overflow prevented by truncating value
		HTTP_READ_INCOMPLETE	// Entire object is not yet in the buffer.  Try again later.
	} HTTP_READ_STATUS;

	// File type definitions
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
		HEADER_UNUSED = 99u,
		HEADER_COOKIE = 0u,
		HEADER_AUTH,
		HEADER_CONTENT_LENGTH,
		HEADER_CONTENT_TYPE,
		HEADER_CONNECTION

	} HEADER_NAME_INDEX;

	typedef enum 
	{  
		HTTP_GET = 0u,
		HTTP_POST,
		HTTP_PUT,
		HTTP_DELETE

	} HTTP_METHOD;

	typedef enum 
	{
		ROUTE_DYNAMIC = 0u,
		ROUTE_STATIC

	} ROUTE_TYPE;

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
		BYTE routeState;							// State machine state for processing request
		DWORD contentLength;
		ROUTE_TYPE routeType;
		void (*callback)(void);

	} HTTP_SERVER_REQUEST;

	typedef struct 
	{
		HTTP_STATUS status;
		HTTP_FILE_TYPE returnType;
		BOOL disableCache;
		HTTP_HEADER headers[5];
		
	} HTTP_SERVER_RESPONSE;

	typedef struct 
	{
		HTTP_SERVER_REQUEST request;
		HTTP_SERVER_RESPONSE response;
		SM_HTTP2 state;
		TCP_SOCKET socket;
		DWORD wdTimer;
		BYTE data[HTTP_MAX_DATA_LEN];	// General purpose data buffer
		DWORD bytesAvailable;
		FILEHANDLE *file;

	} HTTP_SERVER_CONNECTION;

	#define activeSocket		httpConnections[activeConnectionID].socket		// Access the current socket
  #define HTTP_CRLF_LEN 2       // Length of above string

	extern HTTP_SERVER_CONNECTION httpConnections[MAX_HTTP_CONNECTIONS];
	extern BYTE activeConnectionID;

	extern ROM BYTE HTTP_CRLF[HTTP_CRLF_LEN];
	extern ROM char * ROM HTTPSupportedHeaders[];
	extern ROM char * ROM HTTPResponseHeaders[];
	extern ROM char * ROM HTTPRequestHeaders[];
	extern ROM char * ROM httpContentTypes[HTTP_UNKNOWN+1];
	extern ROM char * ROM httpFileExtensions[HTTP_UNKNOWN+1];

	#define activeConnection 			(httpConnections[activeConnectionID])
	#define activeConnectionState (httpConnections[activeConnectionID].state)
	#define activeRequest 				(httpConnections[activeConnectionID].request)
	#define activeResponse  			(httpConnections[activeConnectionID].response)


#if defined(HTTP_SAVE_CONTEXT_IN_PIC_RAM)
	#define RESERVED_HTTP_MEMORY 0ul        // Macro indicating how much RAM to allocate on an ethernet controller to store HTTP state data.
#else
	#define RESERVED_HTTP_MEMORY ((DWORD)MAX_HTTP_CONNECTIONS * (DWORD)sizeof(HTTP_SERVER_REQUEST))
	//#define RESERVED_HTTP_MEMORY ((DWORD)MAX_HTTP_CONNECTIONS * (DWORD)sizeof(HTTP_CONN))
#endif


/****************************************************************************
  Section:
	Function Prototypes
  ***************************************************************************/

void HTTPInit(void);
void HTTPServer(void);


HTTP_IO_RESULT HttpServeResponse(void);


/*****************************************************************************
  Function:
	BYTE HTTPNeedsAuth(BYTE* cFile)

  Summary:
	Determines if a given file name requires authentication

  Description:
	This function is implemented by the application developer in
	CustomHTTPApp.c.  Its function is to determine if a file being
	requested requires authentication to view.  The user name and password,
	if supplied, will arrive later with the request headers, and will be
	processed at that time.

	Return values 0x80 - 0xff indicate that authentication is not required,
	while values from 0x00 to 0x79 indicate that a user name and password
	are required before proceeding.  While most applications will only use a
	single value to grant access and another to require authorization, the
	range allows multiple "realms" or sets of pages to be protected, with
	different credential requirements for each.

	The return value of this function is saved as curHTTP.isAuthorized, and
	will be available to future callbacks, including HTTPCheckAuth and any
	of the HTTPExecuteGet, HTTPExecutePost, or HTTPPrint_varname callbacks.

  Precondition:
	None

  Parameters:
	cFile - the name of the file being requested

  Return Values:
	<= 0x79 - valid authentication is required
	>= 0x80 - access is granted for this connection

  Remarks:
	This function may NOT write to the TCP buffer.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
	BYTE HTTPNeedsAuth(BYTE* cFile);
#endif

/*****************************************************************************
  Function:
	BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)

  Summary:
	Performs validation on a specific user name and password.

  Description:
	This function is implemented by the application developer in
	CustomHTTPApp.c.  Its function is to determine if the user name and
	password supplied by the client are acceptable for this resource.

	The value of curHTTP.isAuthorized will be set to the previous return
	value of HTTPRequiresAuthorization.  This callback function can check
	this value to determine if only specific user names or passwords will
	be accepted for this resource.

	Return values 0x80 - 0xff indicate that the credentials were accepted,
	while values from 0x00 to 0x79 indicate that authorization failed.
	While most applications will only use a single value to grant access,
	flexibility is provided to store multiple values in order to
	indicate which user (or user's group) logged in.

	The return value of this function is saved as curHTTP.isAuthorized, and
	will be available to future callbacks, including any of the
	HTTPExecuteGet, HTTPExecutePost, or HTTPPrint_varname callbacks.

  Precondition:
	None

  Parameters:
	cUser - the user name supplied by the client
	cPass - the password supplied by the client

  Return Values:
	<= 0x79 - the credentials were rejected
	>= 0x80 - access is granted for this connection

  Remarks:
	This function is only called when an Authorization header is
	encountered.

	This function may NOT write to the TCP buffer.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
	BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass);
#endif

#endif
#endif
