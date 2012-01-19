#define APPLICATION_ENTRY_POINT

#include "app.h"

void main()
{
	InitializeSystem();

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
    }
}

void InitializeSystem()
{
	SYSTEMConfigWaitStatesAndPB(CLOCK_FREQ);
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

	//INTEnableSystemMultiVectoredInt();
}
