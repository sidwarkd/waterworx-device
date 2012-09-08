/*********************************************************************
 *
 *  Application to Demo HTTP2 Server
 *  Support for HTTP2 module in Microchip TCP/IP Stack
 *	 -Implements the application 
 *	 -Reference: RFC 1002
 *
 *********************************************************************
 * FileName:        CustomHTTPApp.c
 * Dependencies:    TCP/IP stack
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2010 Microchip Technology Inc.  All rights
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
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Elliott Wood     	6/18/07	    Original
 * Brad Rex             04 Apr 2010 Updated for MRF24WB0M
 ********************************************************************/
#define __CUSTOMHTTPAPP_C

#include <http_server/module.h>

#if defined(STACK_USE_HTTP2_SERVER)

/****************************************************************************
  Section:
	Function Prototypes and Memory Globalizers
  ***************************************************************************/

// bss descriptor fetched from on-chip
static tWFScanResult bssDesc;
static BOOL bssDescIsValid = FALSE;

// RAM allocated for DDNS parameters
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
	static BYTE DDNSData[100];
#endif

// Sticky status message variable.
// This is used to indicated whether or not the previous POST operation was 
// successful.  The application uses these to store status messages when a 
// POST operation redirects.  This lets the application provide status messages
// after a redirect, when connection instance data has already been lost.
static BOOL lastSuccess = FALSE;

// Stick status message variable.  See lastSuccess for details.
static BOOL lastFailure = FALSE;
BYTE sendDataBuffer[512];

static BOOL HTTPServeStaticAsset(void);

/****************************************************************************
  Section:
  String Constants
  ***************************************************************************/
  //static ROM BYTE HTTP_CRLF[] = "\r\n"; // New line sequence




/****************************************************************************
  Section:
	Authorization Handlers
  ***************************************************************************/
  
/*****************************************************************************
  Function:
	BYTE HTTPNeedsAuth(BYTE* cFile)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPNeedsAuth(BYTE* cFile)
{
	// If the filename begins with the folder "protect", then require auth
	if(memcmppgm2ram(cFile, (ROM void*)"protect", 7) == 0)
		return 0x00;		// Authentication will be needed later

	// If the filename begins with the folder "snmp", then require auth
	if(memcmppgm2ram(cFile, (ROM void*)"snmp", 4) == 0)
		return 0x00;		// Authentication will be needed later

	#if defined(HTTP_MPFS_UPLOAD_REQUIRES_AUTH)
	if(memcmppgm2ram(cFile, (ROM void*)"mpfsupload", 10) == 0)
		return 0x00;
	#endif

	// You can match additional strings here to password protect other files.
	// You could switch this and exclude files from authentication.
	// You could also always return 0x00 to require auth for all files.
	// You can return different values (0x00 to 0x79) to track "realms" for below.

	return 0x80;			// No authentication required
}
#endif

/*****************************************************************************
  Function:
	BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
{
	if(strcmppgm2ram((char *)cUser,(ROM char *)"admin") == 0
		&& strcmppgm2ram((char *)cPass, (ROM char *)"microchip") == 0)
		return 0x80;		// We accept this combination
	
	// You can add additional user/pass combos here.
	// If you return specific "realm" values above, you can base this 
	//   decision on what specific file or folder is being accessed.
	// You could return different values (0x80 to 0xff) to indicate 
	//   various users or groups, and base future processing decisions
	//   in HTTPExecuteGet/Post or HTTPPrint callbacks on this value.
	
	return 0x00;			// Provided user/pass is invalid
}
#endif

HTTP_IO_RESULT HTTPExecuteRoute(void)
{
	BYTE *queryStringPos;
	BYTE *ext;
	CHAR filename[128];

	switch(activeRequest.methodState)
	{
		case ROUTE_PROCESS_REQUEST:
			// We need to determine if this is a route that requires dynamic body 
			// generation or if this is just a static asset that we need to serve up
			queryStringPos = strchr(activeRequest.url, '?');
			ext = strchr(activeRequest.url, '.');

			// There is a period that must be a file extension because there is
			// no query string that might contain periods in the data.  This is
			// a simple indicator of a static asset.
			if(ext != NULL && queryStringPos == NULL)
			{
				activeRequest.routeType = ROUTE_STATIC;

	      // Make sure the file exists
  			// Add the root dir to the file
				sprintf(filename, "public%s", activeRequest.url);
	      activeConnection.file = FATFS_fopen(filename, "r");
	      if(activeConnection.file == NULL)
	      {
	      	mLED_Red_Toggle();
	      	activeResponse.status = HTTP_NOT_FOUND;
	      }
	          
	      // Find the extension in the filename
	      ext++;
	      for(activeResponse.returnType = HTTP_TXT; activeResponse.returnType < HTTP_UNKNOWN; activeResponse.returnType++)
	       if(!stricmppgm2ram(ext, (ROM void*)httpFileExtensions[activeResponse.returnType]))
	         break;

	      activeResponse.disableCache = FALSE;
			}
			else
			{
				activeRequest.routeType = ROUTE_DYNAMIC;
				activeResponse.disableCache = TRUE;
			}

			activeRequest.methodState = ROUTE_SERVE_HEADERS;
			return HTTP_IO_WAITING;
			break;

		case ROUTE_SERVE_HEADERS:
			// We're in write mode now:
      // Adjust the TCP FIFOs for optimal transmission of 
      // the HTTP response to the browser
      TCPAdjustFIFOSize(activeSocket, 1, 0, TCP_ADJUST_GIVE_REST_TO_TX);
        
      // Send headers
      TCPPutROMString(activeSocket, (ROM BYTE*)HTTPResponseHeaders[activeResponse.status]);

      // If this is a redirect, print the rest of the Location: header         
      if(activeResponse.status == HTTP_REDIRECT)
      {
        TCPPutString(activeSocket, activeConnection.data);
        TCPPutROMString(activeSocket, (ROM BYTE*)"\r\n\r\n304 Redirect: ");
        TCPPutString(activeSocket, activeConnection.data);
        TCPPutROMString(activeSocket, (ROM BYTE*)HTTP_CRLF);
      }

      // Output the content type, if known
      if(activeResponse.returnType != HTTP_UNKNOWN)
      {
        TCPPutROMString(activeSocket, (ROM BYTE*)"Content-Type: ");
        TCPPutROMString(activeSocket, (ROM BYTE*)httpContentTypes[activeResponse.returnType]);
        TCPPutROMString(activeSocket, HTTP_CRLF);
      }
            
      // Output the cache-control
      if(activeResponse.status == HTTP_OK)
      {
	      TCPPutROMString(activeSocket, (ROM BYTE*)"Cache-Control: ");
	      if(activeRequest.method == HTTP_POST || activeResponse.disableCache == TRUE)
	      {// This is a dynamic page or a POST request, so no cache
	        TCPPutROMString(activeSocket, (ROM BYTE*)"no-cache");
	      }
	      else
	      {// This is a static page, so save it for the specified amount of time
	        TCPPutROMString(activeSocket, (ROM BYTE*)"max-age=");
	        TCPPutROMString(activeSocket, (ROM BYTE*)HTTP_CACHE_LEN);
	      }
	      TCPPutROMString(activeSocket, HTTP_CRLF);
	      
	      // Terminate the headers
	      TCPPutROMString(activeSocket, HTTP_CRLF);
    	}

      TCPFlush(activeSocket);

      // Only move on if we haven't encountered an error
      if(activeResponse.status == HTTP_OK)
      	activeRequest.methodState = ROUTE_SERVE_BODY;
      else
      	activeRequest.methodState = ROUTE_DONE;
  
      // Move to next stage
      //isDone = FALSE;
      return HTTP_IO_WAITING;
      break;

		case ROUTE_SERVE_BODY:
			// Two options here.  We either serving static file content or dynamically
			// building up a response specific to the route requested

			if(activeRequest.routeType == ROUTE_STATIC)
			{
				while(TCPIsPutReady(activeSocket) != 0)
				{
					if(HTTPServeStaticAsset())
					{
						activeRequest.methodState = ROUTE_DONE;
						return HTTP_IO_WAITING;
					}
				}
			}
			else
			{
				// This is a dynamic route and we need to decide what to do
				activeRequest.methodState = ROUTE_DONE;
			}


			return HTTP_IO_WAITING;
			break;

		case ROUTE_DONE:
			return HTTP_IO_DONE;
			break;

	} 
}

/****************************************************************************
  Section:
	GET Form Handlers
  ***************************************************************************/
  
/*****************************************************************************
  Function:
	HTTP_IO_RESULT HTTPExecuteGet(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
HTTP_IO_RESULT HTTPExecuteGet(void)
{
	BYTE *ptr, *ptr1;
	BYTE filename[20];
	
	BYTE bssIdx;
	WORD_VAL bssIdxStr;
	
	//mLED_Red_Toggle();
	// Load the file name
	// Make sure BYTE filename[] above is large enough for your longest name
	//MPFSGetFilename(curHTTP.file, filename, 20);
	
	// If its the forms.htm page
	// if(!memcmppgm2ram(filename, "forms.htm", 9))
	// {
	// 	// Seek out each of the four LED strings, and if it exists set the LED states
	// }
	
	// If it's the LED updater file
	// else if(!memcmppgm2ram(filename, "cookies.htm", 11))
	// {
	// 	// This is very simple.  The names and values we want are already in
	// 	// the data array.  We just set the hasArgs value to indicate how many
	// 	// name/value pairs we want stored as cookies.
	// 	// To add the second cookie, just increment this value.
	// 	// remember to also add a dynamic variable callback to control the printout.
	// 	curHTTP.hasArgs = 0x01;
	// }
		
	
	// If it's the LED updater file
	// else if(!memcmppgm2ram(filename, "stations.cgi", 8))
	// {
	// 	// Determine which LED to toggle
	// 	ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"station");
		
	// 	// Toggle the specified LED
	// 	switch(*ptr) {
	// 		case '1':
	// 			mLED_Green_Toggle();
	// 			mLED_White_Off();
	// 			mLED_Red_Off();
	// 			mLED_Yellow_Off();
	// 			mStation5_Off();
	// 			break;
	// 		case '2':
	// 			mLED_White_Toggle();
	// 			mLED_Green_Off();
	// 			mLED_Red_Off();
	// 			mLED_Yellow_Off();
	// 			mStation5_Off();
	// 			break;
	// 		case '3':
	// 			mLED_Red_Toggle();
	// 			mLED_Green_Off();
	// 			mLED_White_Off();
	// 			mLED_Yellow_Off();
	// 			mStation5_Off();
	// 			break;
	// 		case '4':
	// 			mLED_Yellow_Toggle();
	// 			mLED_Green_Off();
	// 			mLED_White_Off();
	// 			mLED_Red_Off();
	// 			mStation5_Off();
	// 			break;
	// 		case '5':
	// 			mStation5_Toggle();
	// 			mLED_Yellow_Off();
	// 			mLED_Green_Off();
	// 			mLED_White_Off();
	// 			mLED_Red_Off();
	// 			break;
	// 	}
		
	// }
	// else if(!memcmppgm2ram(filename, "scan.cgi", 8))
	// {
	// 	ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"scan");
	// 	ptr1 = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"getBss");
		
	// 	if ((ptr != NULL) && (ptr1 == NULL))
	// 	{
	// 		bssDescIsValid = FALSE;
	// 		// scan request
 //        	if (WFStartScan() == WF_SUCCESS)
	//     	{
 //            	SCAN_SET_DISPLAY(SCANCXT.scanState);
 //            	SCANCXT.displayIdx = 0;
 //        	}
	// 	}
	// 	else if ((ptr == NULL) && (ptr1 != NULL))
	// 	{
	// 		// getBss request
	// 		// use the value to get the nth bss stored on chip
	// 		bssDescIsValid = FALSE;
	// 		bssIdxStr.v[1] = *ptr1;
	// 		bssIdxStr.v[0] = *(ptr1+1);	
	//   		bssIdx = hexatob(bssIdxStr);
	//   		WFRetrieveScanResult(bssIdx, &bssDesc);
	  		
	//   		bssDescIsValid = TRUE;
	// 	}
	// 	else
	// 	{
	// 		// impossible to get here
	// 	}			  	
	// }
	// else
	// {
	// }		
	
	return HTTP_IO_DONE;
}


/****************************************************************************
  Section:
	POST Form Handlers
  ***************************************************************************/
#if defined(HTTP_USE_POST)

/*****************************************************************************
  Function:
	HTTP_IO_RESULT HTTPExecutePost(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
HTTP_IO_RESULT HTTPExecutePost(void)
{
	// Resolve which function to use and pass along
	BYTE filename[20];
	
	// Load the file name
	// Make sure BYTE filename[] above is large enough for your longest name
	//MPFSGetFilename(curHTTP.file, filename, sizeof(filename));

	return HTTP_IO_DONE;
}

static BOOL HTTPServeStaticAsset(void)
{


  static DWORD availbleTcpBuffSize,len;
  static DWORD cntr=0;
  static BYTE lock=0;
  static BYTE nameHashMatched=FALSE;
  static DWORD numBytes,dynVarCntr,dynVarRcrdOffset,dynVarCallBackID,bytesReadCount=0;
  DWORD UInt32DataFromBinFile;
  WORD UInt16DataFromBinFile,nameHashRcrd;
  DWORD recrdcntr=0;
  
  signed char chdirRetVal;

  static enum
  {
  	SM_IDLE = 0u,
    SM_SERVE_TEXT_DATA,     
    SM_CLOSE_FILE

  }smHTTPSendFile = SM_IDLE;

  switch(smHTTPSendFile)
  {

  	case SM_IDLE:
  		numBytes = FATFS_fsize(activeConnection.file);

    case SM_SERVE_TEXT_DATA:

      // If HashIndex do not match,that means no entry in the "FilRcrd.bin", means no dynamic variables for this wepage,
      //then proceed to serve the page as normal HTML text
    	memset(sendDataBuffer, 0, sizeof(sendDataBuffer));
    	
      availbleTcpBuffSize = TCPIsPutReady(activeSocket);
      
      if(availbleTcpBuffSize >= 512)
      {
        if(numBytes >= 512)
        {
          len=FATFS_fread(sendDataBuffer, 1, 512, activeConnection.file);
          TCPPutArray(activeSocket, sendDataBuffer, len);
          numBytes -= len;
        }
        else
        {
          len=FATFS_fread(sendDataBuffer, 1, numBytes, activeConnection.file);
          TCPPutArray(activeSocket, sendDataBuffer, len);
          numBytes = 0;

        }
      }
      else if(availbleTcpBuffSize != 0)
      {
        if(numBytes >= availbleTcpBuffSize)
        {
          len=FATFS_fread(sendDataBuffer, 1, availbleTcpBuffSize, activeConnection.file);
          TCPPutArray(activeSocket, sendDataBuffer, len);
          numBytes -= len;
        }
        else 
        {
          len=FATFS_fread(sendDataBuffer, 1, numBytes, activeConnection.file);
          TCPPutArray(activeSocket, sendDataBuffer, numBytes);
          numBytes = 0;
          
        }
      }
      if(numBytes <= 100)
      {
        numBytes=numBytes;
      }
      if(numBytes == 0)
      {
        TCPFlush(activeSocket);

        FATFS_fclose(activeConnection.file);

        smHTTPSendFile=SM_IDLE;
        bytesReadCount=0;
        return TRUE;
      }

      TCPFlush(activeSocket);
      break;

    default:
      return FALSE;
        
  }

  if(FATFS_feof(activeConnection.file) || numBytes == 0)
  {
    TCPFlush(activeSocket);
    
    FATFS_fclose(activeConnection.file);
            
    smHTTPSendFile=SM_IDLE;
    return TRUE;
  }

  return FALSE;
}

#endif // if post

#endif
