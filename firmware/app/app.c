#define APPLICATION_ENTRY_POINT

#include "app.h"

void _general_exception_handler(unsigned cause, unsigned status)
{
	mLED_Red_On();
	SERIALUSB_Write("An exception occurred!!!");
	Nop();
	Nop();
}

/*void DisplayStatusCode(HttpResponse *response)
{
    CHAR status[5];
    itoa(status, response->status_code, 10);
    SERIALUSB_Write(status);
    CurrentPacket = NULL;
}

void DisplayResponseBody(HttpResponse *response)
{
	SERIALUSB_Write(response->body);
}

void LogResponseBody(HttpResponse *response)
{
	FILEHANDLE file;
	char buff[256];

	DateTimeToString(Now(), &buff[0]);
	if(OpenFile("http.log", &file, FA_WRITE | FA_OPEN_ALWAYS) == TRUE)
	{
		WriteFile(buff, &file);
		WriteFile(response->body, &file);
		WriteFile("\r\n", &file);
		CloseFile(&file);
	}
	else
	{
		SERIALUSB_Write("Unable to open file\r\n");
	}

	SERIALUSB_Write(response->body);
}*/

int main(void)
{
	#ifndef TESTING

	InitializeSystem();

    while(1)
    {
    	/*if(mSwitch_Prog == SWITCH_PRESSED)
    	{
    		//WIFI_PerformGet((CHAR*)"waterworx.herokuapp.com", (CHAR*)"/", DisplayResponseBody);
    		//WIFI_PerformPost((CHAR*)"waterworx.herokuapp.com", (CHAR*)"/", json, DisplayResponseBody);
    	}

    	if(mSwitch_User == SWITCH_PRESSED)
    	{
				
    	}
        */
    	if(mRtccGetIntFlag())
    	{
    		//mLED_Red_Toggle();
    		mRtccClrIntFlag();
            SPRINKLER_Initialize();
    	}

		SPRINKLER_ProcessTasks();
    	WIFI_PerformStackTasks();
    	SERIALUSB_ProcessTasks();
    }
  #else
  // Testing mode
  InitializeSystem();

  while(1)
  {
  	if(mSwitch_Prog == SWITCH_PRESSED)
  	{
  		Modules[0] = RTCC_GetTestModule();
  		RunAllTests();
  		DisplayTestResults();
  	}

  	SERIALUSB_ProcessTasks();
  }
  #endif
}

void InitializeSystem()
{
	SYSTEMConfigWaitStatesAndPB(CLOCK_FREQ);
	mOSCSetPBDIV(OSC_PB_DIV_4);  // Set to get 20MHz PB clock
	CheKseg0CacheOn();
	mJTAGPortEnable(0);

	// Initialize the pins to all digital output and driven to ground.
	// Exception is RE7 and RE6 which are switch inputs
	PORTSetPinsDigitalIn(IOPORT_E, BIT_6);
	PORTSetPinsDigitalIn(IOPORT_E, BIT_7);

	mPORTASetPinsDigitalOut(0xFFFF);
	mPORTBSetPinsDigitalOut(0xFFFF);
	mPORTCSetPinsDigitalOut(0xFFFF);
	mPORTDSetPinsDigitalOut(0xFFFF);
	mPORTESetPinsDigitalOut(0xFF3F);
	mPORTFSetPinsDigitalOut(0xFFFF);
	mPORTGSetPinsDigitalOut(0xFFFF);

	mPORTAClearBits(0xFFFF);
	mPORTBClearBits(0xFFFF);
	mPORTCClearBits(0xFFFF);
	mPORTDClearBits(0xFFFF);
	mPORTEClearBits(0xFF3F);
	mPORTESetBits(0x000F);		// LED latches need to be set high for off
	mPORTFClearBits(0xFFFF);
	mPORTGClearBits(0xFFFF);

	INTEnableSystemMultiVectoredInt();
	
	//LCD_Initialize();
	WIFI_Initialize();
	//SPRINKLER_Initialize();
	RTCC_Initialize(); 
	SERIALUSB_Initialize();
	SDCARD_Initialize();
	
	// RTCC Time 0xhhmmss00
	// RTCC Date 0xyymmddww where ww is the integer of the weekday 0=Sunday
	//RtccOpen(0x10300000, 0x12021604, 0);
	//while((RtccGetClkStat() != RTCC_CLK_ON));
	RtccSetAlarmDate(0x00042904);
	RtccSetAlarmTime(0x10303000);
	
	RtccSetAlarmRpt(RTCC_RPT_TEN_SEC);
	RtccSetAlarmRptCount(3);
	//RtccChimeEnable();
	RtccAlarmEnable();

}
