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
	
	mLED_Red_Toggle();
	// Load the file name
	// Make sure BYTE filename[] above is large enough for your longest name
	MPFSGetFilename(curHTTP.file, filename, 20);
	
	// If its the forms.htm page
	if(!memcmppgm2ram(filename, "forms.htm", 9))
	{
		// Seek out each of the four LED strings, and if it exists set the LED states
	}
	
	// If it's the LED updater file
	else if(!memcmppgm2ram(filename, "cookies.htm", 11))
	{
		// This is very simple.  The names and values we want are already in
		// the data array.  We just set the hasArgs value to indicate how many
		// name/value pairs we want stored as cookies.
		// To add the second cookie, just increment this value.
		// remember to also add a dynamic variable callback to control the printout.
		curHTTP.hasArgs = 0x01;
	}
		
	
	// If it's the LED updater file
	else if(!memcmppgm2ram(filename, "stations.cgi", 8))
	{
		// Determine which LED to toggle
		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"station");
		
		// Toggle the specified LED
		switch(*ptr) {
			case '1':
				mLED_Green_On();
				mLED_White_Off();
				mLED_Red_Off();
				mLED_Yellow_Off();
				break;
			case '2':
				mLED_White_On();
				mLED_Green_Off();
				mLED_Red_Off();
				mLED_Yellow_Off();
				break;
			case '3':
				mLED_Red_On();
				mLED_Green_Off();
				mLED_White_Off();
				mLED_Yellow_Off();
				break;
			case '4':
				mLED_Yellow_On();
				mLED_Green_Off();
				mLED_White_Off();
				mLED_Red_Off();
				break;
		}
		
	}
	else if(!memcmppgm2ram(filename, "scan.cgi", 8))
	{
		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"scan");
		ptr1 = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"getBss");
		
		if ((ptr != NULL) && (ptr1 == NULL))
		{
			bssDescIsValid = FALSE;
			// scan request
        	if (WFStartScan() == WF_SUCCESS)
	    	{
            	SCAN_SET_DISPLAY(SCANCXT.scanState);
            	SCANCXT.displayIdx = 0;
        	}
		}
		else if ((ptr == NULL) && (ptr1 != NULL))
		{
			// getBss request
			// use the value to get the nth bss stored on chip
			bssDescIsValid = FALSE;
			bssIdxStr.v[1] = *ptr1;
			bssIdxStr.v[0] = *(ptr1+1);	
	  		bssIdx = hexatob(bssIdxStr);
	  		WFRetrieveScanResult(bssIdx, &bssDesc);
	  		
	  		bssDescIsValid = TRUE;
		}
		else
		{
			// impossible to get here
		}			  	
	}
	else
	{
	}		
	
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
	MPFSGetFilename(curHTTP.file, filename, sizeof(filename));

	return HTTP_IO_DONE;
}


#endif //(use_post)


/****************************************************************************
  Section:
	Dynamic Variable Callback Functions
  ***************************************************************************/

/*****************************************************************************
  Function:
	void HTTPPrint_varname(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
void HTTPPrint_builddate(void)
{
    curHTTP.callbackPos = 0x01;
    if(TCPIsPutReady(sktHTTP) < strlenpgm((ROM char*)__DATE__" ""00:08:00"))
        return;
 
    curHTTP.callbackPos = 0x00;
    TCPPutROMString(sktHTTP, (ROM void*)__DATE__" ""00:08:00");
}

void HTTPPrint_version(void)
{
	TCPPutROMString(sktHTTP, (ROM void*)TCPIP_STACK_VERSION);
}




ROM BYTE HTML_UP_ARROW[] = "up";
ROM BYTE HTML_DOWN_ARROW[] = "dn";

void HTTPPrint_btn(WORD num)
{
	// Determine which button
	switch(num)
	{
		case 0:
			//num = BUTTON0_IO;
			break;
		case 1:
			//num = BUTTON1_IO;
			break;
		case 2:
			//num = BUTTON2_IO;
			break;
		case 3:
			//num = BUTTON3_IO;
			break;
		default:
			num = 0;
	}

	// Print the output
	TCPPutROMString(sktHTTP, (num?HTML_UP_ARROW:HTML_DOWN_ARROW));
	return;
}
	
void HTTPPrint_led(WORD num)
{
	// Determine which LED
	switch(num)
	{
		case 0:
			//num = LED0_IO;
			break;
		case 1:
			//num = LED1_IO;
			break;
		case 2:
			//num = LED2_IO;
			break;
		case 3:
			//num = LED3_IO;
			break;
		case 4:
			//num = LED4_IO;
			break;
		case 5:
			//num = LED5_IO;
			break;
		case 6:
			//num = LED6_IO;
			break;
		case 7:
			//num = LED7_IO;
			break;

		default:
			num = 0;
	}

	// Print the output
	TCPPut(sktHTTP, (num?'1':'0'));
	return;
}

void HTTPPrint_ledSelected(WORD num, WORD state)
{
	// Determine which LED to check
	switch(num)
	{
		case 0:
			//num = LED0_IO;
			break;
		case 1:
			//num = LED1_IO;
			break;
		case 2:
			//num = LED2_IO;
			break;
		case 3:
			//num = LED3_IO;
			break;
		case 4:
			//num = LED4_IO;
			break;
		case 5:
			//num = LED5_IO;
			break;
		case 6:
			//num = LED6_IO;
			break;
		case 7:
			//num = LED7_IO;
			break;

		default:
			num = 0;
	}
	
	// Print output if TRUE and ON or if FALSE and OFF
	if((state && num) || (!state && !num))
		TCPPutROMString(sktHTTP, (ROM BYTE*)"SELECTED");
	return;
}

void HTTPPrint_pot(void)
{
	BYTE AN0String[8];
	WORD ADval;

#if defined(__18CXX)
    // Wait until A/D conversion is done
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);

    // Convert 10-bit value into ASCII string
    ADval = (WORD)ADRES;
    //ADval *= (WORD)10;
    //ADval /= (WORD)102;
    uitoa(ADval, AN0String);
#else
	ADval = (WORD)ADC1BUF0;
	//ADval *= (WORD)10;
	//ADval /= (WORD)102;
    uitoa(ADval, (BYTE*)AN0String);
#endif

   	TCPPutString(sktHTTP, AN0String);
}

void HTTPPrint_lcdtext(void)
{
	WORD len;

	// Determine how many bytes we can write
	len = TCPIsPutReady(sktHTTP);
	
	#if defined(USE_LCD)
	// If just starting, set callbackPos
	if(curHTTP.callbackPos == 0u)
		curHTTP.callbackPos = 32;
	
	// Write a byte at a time while we still can
	// It may take up to 12 bytes to write a character
	// (spaces and newlines are longer)
	while(len > 12u && curHTTP.callbackPos)
	{
		// After 16 bytes write a newline
		if(curHTTP.callbackPos == 16u)
			len -= TCPPutROMArray(sktHTTP, (ROM BYTE*)"<br />", 6);

		if(LCDText[32-curHTTP.callbackPos] == ' ' || LCDText[32-curHTTP.callbackPos] == '\0')
			len -= TCPPutROMArray(sktHTTP, (ROM BYTE*)"&nbsp;", 6);
		else
			len -= TCPPut(sktHTTP, LCDText[32-curHTTP.callbackPos]);

		curHTTP.callbackPos--;
	}
	#else
	TCPPutROMString(sktHTTP, (ROM BYTE*)"No LCD Present");
	#endif

	return;
}

void HTTPPrint_hellomsg(void)
{
	BYTE *ptr;
	
	ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE*)"name");
	
	// We omit checking for space because this is the only data being written
	if(ptr != NULL)
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"Hello, ");
		TCPPutString(sktHTTP, ptr);
	}

	return;
}

void HTTPPrint_cookiename(void)
{
	BYTE *ptr;
	
	ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE*)"name");
	
	if(ptr)
		TCPPutString(sktHTTP, ptr);
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"not set");
	
	return;
}

void HTTPPrint_uploadedmd5(void)
{
	BYTE i;

	// Set a flag to indicate not finished
	curHTTP.callbackPos = 1;
	
	// Make sure there's enough output space
	if(TCPIsPutReady(sktHTTP) < 32u + 37u + 5u)
		return;

	// Check for flag set in HTTPPostMD5
#if defined(STACK_USE_HTTP_MD5_DEMO)
	if(curHTTP.smPost != SM_MD5_POST_COMPLETE)
#endif
	{// No file uploaded, so just return
		TCPPutROMString(sktHTTP, (ROM BYTE*)"<b>Upload a File</b>");
		curHTTP.callbackPos = 0;
		return;
	}
	
	TCPPutROMString(sktHTTP, (ROM BYTE*)"<b>Uploaded File's MD5 was:</b><br />");
	
	// Write a byte of the md5 sum at a time
	for(i = 0; i < 16u; i++)
	{
		TCPPut(sktHTTP, btohexa_high(curHTTP.data[i]));
		TCPPut(sktHTTP, btohexa_low(curHTTP.data[i]));
		if((i & 0x03) == 3u)
			TCPPut(sktHTTP, ' ');
	}
	
	curHTTP.callbackPos = 0x00;
	return;
}

extern APP_CONFIG AppConfig;

void HTTPPrintIP(IP_ADDR ip)
{
	BYTE digits[4];
	BYTE i;
	
	for(i = 0; i < 4u; i++)
	{
		if(i)
			TCPPut(sktHTTP, '.');
		uitoa(ip.v[i], digits);
		TCPPutString(sktHTTP, digits);
	}
}

void HTTPPrint_config_hostname(void)
{
	TCPPutString(sktHTTP, AppConfig.NetBIOSName);
	return;
}

void HTTPPrint_config_dhcpchecked(void)
{
	if(AppConfig.Flags.bIsDHCPEnabled)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"checked");
	return;
}

void HTTPPrint_config_ip(void)
{
	HTTPPrintIP(AppConfig.MyIPAddr);
	return;
}

void HTTPPrint_config_gw(void)
{
	HTTPPrintIP(AppConfig.MyGateway);
	return;
}

void HTTPPrint_config_subnet(void)
{
	HTTPPrintIP(AppConfig.MyMask);
	return;
}

void HTTPPrint_config_dns1(void)
{
	HTTPPrintIP(AppConfig.PrimaryDNSServer);
	return;
}

void HTTPPrint_config_dns2(void)
{
	HTTPPrintIP(AppConfig.SecondaryDNSServer);
	return;
}

void HTTPPrint_config_mac(void)
{
	BYTE i;
	
	if(TCPIsPutReady(sktHTTP) < 18u)
	{//need 17 bytes to write a MAC
		curHTTP.callbackPos = 0x01;
		return;
	}	
	
	// Write each byte
	for(i = 0; i < 6u; i++)
	{
		if(i)
			TCPPut(sktHTTP, ':');
		TCPPut(sktHTTP, btohexa_high(AppConfig.MyMACAddr.v[i]));
		TCPPut(sktHTTP, btohexa_low(AppConfig.MyMACAddr.v[i]));
	}
	
	// Indicate that we're done
	curHTTP.callbackPos = 0x00;
	return;
}


// SNMP Read communities configuration page
void HTTPPrint_read_comm(WORD num)
{
	#if defined(STACK_USE_SNMP_SERVER)
	// Ensure no one tries to read illegal memory addresses by specifying 
	// illegal num values.
	if(num >= SNMP_MAX_COMMUNITY_SUPPORT)
		return;
		
	// Send proper string
	TCPPutString(sktHTTP, AppConfig.readCommunity[num]);
	#endif
}

// SNMP Write communities configuration page
void HTTPPrint_write_comm(WORD num)
{
	#if defined(STACK_USE_SNMP_SERVER)
	// Ensure no one tries to read illegal memory addresses by specifying 
	// illegal num values.
	if(num >= SNMP_MAX_COMMUNITY_SUPPORT)
		return;
		
	// Send proper string
	TCPPutString(sktHTTP, AppConfig.writeCommunity[num]);
	#endif
}


void HTTPPrint_reboot(void)
{
	// This is not so much a print function, but causes the board to reboot
	// when the configuration is changed.  If called via an AJAX call, this
	// will gracefully reset the board and bring it back online immediately
	Reset();
}

void HTTPPrint_rebootaddr(void)
{// This is the expected address of the board upon rebooting
	TCPPutString(sktHTTP, curHTTP.data);	
}

void HTTPPrint_ddns_user(void)
{
	#if defined(STACK_USE_DYNAMICDNS_CLIENT)
	if(DDNSClient.ROMPointers.Username || !DDNSClient.Username.szRAM)
		return;
	if(curHTTP.callbackPos == 0x00u)
		curHTTP.callbackPos = (PTR_BASE)DDNSClient.Username.szRAM;
	curHTTP.callbackPos = (PTR_BASE)TCPPutString(sktHTTP, (BYTE*)(PTR_BASE)curHTTP.callbackPos);
	if(*(BYTE*)(PTR_BASE)curHTTP.callbackPos == '\0')
		curHTTP.callbackPos = 0x00;
	#endif
}

void HTTPPrint_ddns_pass(void)
{
	#if defined(STACK_USE_DYNAMICDNS_CLIENT)
	if(DDNSClient.ROMPointers.Password || !DDNSClient.Password.szRAM)
		return;
	if(curHTTP.callbackPos == 0x00u)
		curHTTP.callbackPos = (PTR_BASE)DDNSClient.Password.szRAM;
	curHTTP.callbackPos = (PTR_BASE)TCPPutString(sktHTTP, (BYTE*)(PTR_BASE)curHTTP.callbackPos);
	if(*(BYTE*)(PTR_BASE)curHTTP.callbackPos == '\0')
		curHTTP.callbackPos = 0x00;
	#endif
}

void HTTPPrint_ddns_host(void)
{
	#if defined(STACK_USE_DYNAMICDNS_CLIENT)
	if(DDNSClient.ROMPointers.Host || !DDNSClient.Host.szRAM)
		return;
	if(curHTTP.callbackPos == 0x00u)
		curHTTP.callbackPos = (PTR_BASE)DDNSClient.Host.szRAM;
	curHTTP.callbackPos = (PTR_BASE)TCPPutString(sktHTTP, (BYTE*)(PTR_BASE)curHTTP.callbackPos);
	if(*(BYTE*)(PTR_BASE)curHTTP.callbackPos == '\0')
		curHTTP.callbackPos = 0x00;
	#endif
}

extern ROM char * ROM ddnsServiceHosts[];
void HTTPPrint_ddns_service(WORD i)
{
	#if defined(STACK_USE_DYNAMICDNS_CLIENT)
	if(!DDNSClient.ROMPointers.UpdateServer || !DDNSClient.UpdateServer.szROM)
		return;
	if((ROM char*)DDNSClient.UpdateServer.szROM == ddnsServiceHosts[i])
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	#endif
}


void HTTPPrint_ddns_status(void)
{
	#if defined(STACK_USE_DYNAMICDNS_CLIENT)
	DDNS_STATUS s;
	s = DDNSGetLastStatus();
	if(s == DDNS_STATUS_GOOD || s == DDNS_STATUS_UNCHANGED || s == DDNS_STATUS_NOCHG)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"ok");
	else if(s == DDNS_STATUS_UNKNOWN)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"unk");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"fail");
	#else
	TCPPutROMString(sktHTTP, (ROM BYTE*)"fail");
	#endif
}

void HTTPPrint_ddns_status_msg(void)
{
	if(TCPIsPutReady(sktHTTP) < 75u)
	{
		curHTTP.callbackPos = 0x01;
		return;
	}

	#if defined(STACK_USE_DYNAMICDNS_CLIENT)
	switch(DDNSGetLastStatus())
	{
		case DDNS_STATUS_GOOD:
		case DDNS_STATUS_NOCHG:
			TCPPutROMString(sktHTTP, (ROM BYTE*)"The last update was successful.");
			break;
		case DDNS_STATUS_UNCHANGED:
			TCPPutROMString(sktHTTP, (ROM BYTE*)"The IP has not changed since the last update.");
			break;
		case DDNS_STATUS_UPDATE_ERROR:
		case DDNS_STATUS_CHECKIP_ERROR:
			TCPPutROMString(sktHTTP, (ROM BYTE*)"Could not communicate with DDNS server.");
			break;
		case DDNS_STATUS_INVALID:
			TCPPutROMString(sktHTTP, (ROM BYTE*)"The current configuration is not valid.");
			break;
		case DDNS_STATUS_UNKNOWN:
			TCPPutROMString(sktHTTP, (ROM BYTE*)"The Dynamic DNS client is pending an update.");
			break;
		default:
			TCPPutROMString(sktHTTP, (ROM BYTE*)"An error occurred during the update.<br />The DDNS Client is suspended.");
			break;
	}
	#else
	TCPPutROMString(sktHTTP, (ROM BYTE*)"The Dynamic DNS Client is not enabled.");
	#endif
	
	curHTTP.callbackPos = 0x00;
}

void HTTPPrint_smtps_en(void)
{
	#if defined(STACK_USE_SSL_CLIENT)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"inline");
	#else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"none");
	#endif
}

void HTTPPrint_snmp_en(void)
{
	#if defined(STACK_USE_SNMP_SERVER)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"none");
	#else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"block");
	#endif
}

void HTTPPrint_status_ok(void)
{
	if(lastSuccess)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"block");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"none");
	lastSuccess = FALSE;
}

void HTTPPrint_status_fail(void)
{
	if(lastFailure)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"block");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"none");
	lastFailure = FALSE;
}

void HTTPPrint_scan(void)
{
	BYTE scanInProgressString[4];
	
	uitoa(IS_SCAN_IN_PROGRESS(SCANCXT.scanState), scanInProgressString);
	TCPPutString(sktHTTP, scanInProgressString);
}

void HTTPPrint_fwver(void)
{
	tWFDeviceInfo deviceInfo;
	BYTE fwVerString[8];
	
	WF_GetDeviceInfo(&deviceInfo);
	
	uitoa((deviceInfo.romVersion << 8) | deviceInfo.patchVersion, fwVerString);
	TCPPutString(sktHTTP, fwVerString);
}

void HTTPPrint_ssid(void)
{
	BYTE ssidString[33];
	BYTE ssidLength;
	
	BYTE connState;
	BYTE currCpId;
	
	WF_CMGetConnectionState(&connState, &currCpId);
	
	// we don't need to check the connection state as the only way this function
	// is called is from the webserver.  if the webserver is requesting this,
	// then you can infer that we should be connected to the network
	WF_CPGetSsid(currCpId, ssidString, &ssidLength);		
	
	TCPPutArray(sktHTTP, ssidString, ssidLength);
}	

void HTTPPrint_bssCount(void)
{
	BYTE bssCountString[4];
	
	uitoa(SCANCXT.numScanResults, bssCountString);
	TCPPutString(sktHTTP, bssCountString);
}

void HTTPPrint_valid(void)
{
	BYTE bssDescIsValidString[4];
	
	uitoa((BYTE)bssDescIsValid, bssDescIsValidString);
	TCPPutString(sktHTTP, bssDescIsValidString);
}	

void HTTPPrint_name(void)
{
	if (bssDescIsValid)
	{
		TCPPutString(sktHTTP, bssDesc.ssid);
	}
	else
	{
		TCPPutROMString(sktHTTP, (ROM BYTE *)"0");
	}		
}	

void HTTPPrint_privacy(void)
{
	BYTE security = (bssDesc.apConfig & 0xd0) >> 4;
	BYTE secString[4];
	
	if (bssDescIsValid)
	{
		uitoa(security, secString);
		TCPPutString(sktHTTP, secString);
	}
	else
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"0");
	}	
}	

void HTTPPrint_wlan(void)
{
	BYTE bssTypeString[4];
	if (bssDescIsValid)
	{
		uitoa(bssDesc.bssType, bssTypeString);
		TCPPutString(sktHTTP, bssTypeString);
	}
	else
	{	
		TCPPutROMString(sktHTTP, (ROM BYTE*)"0");
	}	
}	

void HTTPPrint_strength(void)
{
	BYTE strVal;
	BYTE strString[4];
	
	if (bssDescIsValid)
	{
		if (bssDesc.rssi < 121)
		{
			strVal = 1;
		}
		else if (bssDesc.rssi < 141)
		{
			strVal = 2;
		}
		else if (bssDesc.rssi < 161)
		{
			strVal = 3;
		}
		else
		{
			strVal = 4;
		}
		
		uitoa(strVal, strString);
		TCPPutString(sktHTTP, strString);
	}
	else
	{				
		TCPPutROMString(sktHTTP, (ROM BYTE*)"0");
	}
}

void HTTPPrint_nextSSID(void)
{
    TCPPutString(sktHTTP, (BYTE*)CFGCXT.ssid);
}
void HTTPPrint_prevSSID(void)
{
    TCPPutString(sktHTTP, (BYTE*)CFGCXT.prevSSID);
}
void HTTPPrint_prevWLAN(void)
{
    if (CFGCXT.prevWLAN == WF_INFRASTRUCTURE)
    {
        TCPPutROMString(sktHTTP, (ROM BYTE*)"infrastructure (BSS)");
    }
    else
    {
        TCPPutROMString(sktHTTP, (ROM BYTE*)"adhoc (IBSS)");
    }
}
void HTTPPrint_nextWLAN(void)
{
    if (CFGCXT.type == WF_INFRASTRUCTURE)
    {
        TCPPutROMString(sktHTTP, (ROM BYTE*)"infrastructure (BSS)");
    }
    else if (CFGCXT.type == WF_ADHOC)
    {
        TCPPutROMString(sktHTTP, (ROM BYTE*)"adhoc (IBSS)");
    }
    else
    {
        TCPPutROMString(sktHTTP, (ROM BYTE*)"unknown");
    }
}

#endif
