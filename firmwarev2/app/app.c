#define APPLICATION_ENTRY_POINT

#include "app.h"

#define SaveAppConfig(a)

void _general_exception_handler(unsigned cause, unsigned status)
{
	mLED_Red_On();
	Nop();
	Nop();
}

int main(void)
{
	#ifndef TESTING

	InitializeSystem();

    while(1)
    {
    	if(mSwitch_Prog == SWITCH_PRESSED)
    	{
    		//WIFI_PerformGet((CHAR*)"waterworx.herokuapp.com", (CHAR*)"/", DisplayResponseBody);
    		//WIFI_PerformPost((CHAR*)"waterworx.herokuapp.com", (CHAR*)"/", json, DisplayResponseBody);
            mLED_White_Toggle();
    	}

    	if(mSwitch_User == SWITCH_PRESSED)
    	{
			mLED_Yellow_Toggle();
    	}
        
    	/*if(mRtccGetIntFlag())
    	{
    		//mLED_Red_Toggle();
    		mRtccClrIntFlag();
            SPRINKLER_Initialize();
    	}*/

        /*if(GetCurrentDateTimeAsDWORD() > GetDateTimeAsDWORD(&alarmTime))
        {
            SPRINKLER_Initialize();
        }*/
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
	//WIFI_Initialize();
	//SPRINKLER_Initialize();
	//RTCC_Initialize(); 
	//SERIALUSB_Initialize();
	//SDCARD_Initialize();
}