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
    CurrentPacket = NULL;
}

void DisplayResponseBody(HttpResponse *response)
{
	LCD_Write(response->body);
}

int main(void)
{
	static CHAR *json = "{\"did\":\"123456\",\"name\":\"prototype\"}";

	InitializeSystem();

	#ifdef DEBUGGING
	//LCD_Write("App Start");
	#endif

    while(1)
    {
    	if(mSwitch_Prog == SWITCH_PRESSED)
    	{
    		//WIFI_PerformGet((CHAR*)"waterworx.herokuapp.com", (CHAR*)"/", DisplayResponseBody);
    		WIFI_PerformPost((CHAR*)"waterworx.herokuapp.com", (CHAR*)"/", json, DisplayResponseBody);
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
