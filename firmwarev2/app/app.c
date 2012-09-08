#define APPLICATION_ENTRY_POINT

#include "app.h"

#define SaveAppConfig(a)

void Error(void);

void _general_exception_handler(unsigned cause, unsigned status)
{
	mLED_Yellow_On();
	Nop();
	Nop();
  Error();
}

int main(void)
{
	InitializeSystem();

  if(!SDCARD_Mount())
  {
    // Something went wrong with the SD card.  We can't go any further
    Error();
  }

    while(1)
    {
    	if(mSwitch_User == SWITCH_PRESSED)
    	{
    		//WIFI_PerformGet((CHAR*)"waterworx.herokuapp.com", (CHAR*)"/", DisplayResponseBody);
    		//WIFI_PerformPost((CHAR*)"waterworx.herokuapp.com", (CHAR*)"/", json, DisplayResponseBody);
       
        //mLED_Red_Toggle();
        //DelayMs(1000);
        //mLED_Yellow_Toggle();
        //DelayMs(1000); 
    	}
        

    	if(mSwitch_Prog == SWITCH_PRESSED)
    	{
			  //mLED_Green_Toggle();
        //DelayMs(1000);
        //mLED_White_Toggle();
        //DelayMs(1000);
        /*

        mLED_Green_Toggle();
        DelayMs(1000);
        mLED_White_Toggle();
        DelayMs(1000);
        mLED_Red_Toggle();
        DelayMs(1000);
        mLED_Yellow_Toggle();
        DelayMs(1000);*/

        /*mLED_White_On();
        if(OpenFile("program.txt", &fp, FA_CREATE_NEW | FA_WRITE))
        {
          WriteFile("You pressed the program button.", &fp);
          CloseFile(&fp);
          DelayMs(2000);
          mLED_White_Off();
        }
        else
        {
          mLED_Red_On();
        }*/


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

        TCPIP_PerformStackTasks();
        //SERIALUSB_ProcessTasks();
    }
}

void InitializeSystem()
{
	SYSTEMConfigWaitStatesAndPB(CLOCK_FREQ);
	mOSCSetPBDIV(OSC_PB_DIV_4);  // Set to get 20MHz PB clock
  //mOSCSetPBDIV(OSC_PB_DIV_2);
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

  #ifdef SANITY_CHECK
  mLED_Green_On();
  #endif
	
	//LCD_Initialize();
	//WIFI_Initialize();
	//SPRINKLER_Initialize();
	//RTCC_Initialize(); 
  //SERIALUSB_Initialize();
	SDCARD_Initialize();

  TCPIP_Initialize();
}

void Error()
{
  while(1)
  {
    mLED_Red_Toggle();
    DelayMs(200);
  }
}
