#define APPLICATION_ENTRY_POINT

#include "app.h"

void _general_exception_handler(unsigned cause, unsigned status)
{
	mLED_Red_On();
	Nop();
	Nop();
}

void DisplayStatusCode(HttpResponse *response)
{
    CHAR status[5];
    itoa(status, response->status_code, 10);
    LCD_Write(status);
    LCD_Write("done");
    CurrentPacket = NULL;
}

int main(void)
{
	BYTE i = 0;
	InitializeSystem();

	LCD_Write("App Start");

    while(1)
    {
    	// If the USER switch is pressed light up the LED for a second and continue
    	if(mSwitch_User == SWITCH_PRESSED)
    	{
    		mLED_Yellow_On();
    		DelayMs(1000);
    		mLED_Yellow_Off();
    		DelayMs(1000);
    		mLED_Red_On();
    		DelayMs(1000);
    		mLED_Red_Off();
    		DelayMs(1000);
    		mLED_White_On();
    		DelayMs(1000);
    		mLED_White_Off();
    		DelayMs(1000);
    		mLED_Green_On();
    		DelayMs(1000);
    		mLED_Green_Off();
    	}

    	if(mSwitch_Prog == SWITCH_PRESSED)
    	{
    		if(i == 0)
    			WIFI_PerformGet((CHAR*)"hardlysoftware.com", (CHAR*)"/dummy", DisplayStatusCode);
    		else
    			WIFI_PerformGet((CHAR*)"hardlysoftware.com", (CHAR*)"/", DisplayStatusCode);
    		i^=1;
    	}

    	WIFI_PerformStackTasks();
    }
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
	
	LCD_Initialize();
	WIFI_Initialize();
}
