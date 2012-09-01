#define APPLICATION_ENTRY_POINT

#include "app.h"

//#define PROGRAM1

void _general_exception_handler(unsigned cause, unsigned status)
{
	mLED_Red_On();
	Nop();
	Nop();
}

void Error(void);

int main(void)
{

  InitializeSystem();

  while(1)
  {
    #ifdef PROGRAM1
    mLED_Green_Toggle();
    DelayMs(200);
    mLED_White_Toggle();
    DelayMs(200);
    mLED_Red_Toggle();
    DelayMs(200);
    mLED_Yellow_Toggle();
    DelayMs(200);
    #else
    mLED_Yellow_Toggle();
    DelayMs(200);
    mLED_Red_Toggle();
    DelayMs(200);
    mLED_White_Toggle();
    DelayMs(200);
    mLED_Green_Toggle();
    DelayMs(200);
    #endif
  }
}

void InitializeSystem()
{
	SYSTEMConfigWaitStatesAndPB(CLOCK_FREQ);
  mOSCSetPBDIV(OSC_PB_DIV_4);  // Set to get 20MHz PB clock
	CheKseg0CacheOn();
	mJTAGPortEnable(0);
	
	mPORTASetPinsDigitalOut(0xFFFF);
	mPORTBSetPinsDigitalOut(0xFFFF);
	mPORTCSetPinsDigitalOut(0xFFFF);
	mPORTDSetPinsDigitalOut(0xFFFF);
	mPORTESetPinsDigitalOut(0xFF3F);
	mPORTFSetPinsDigitalOut(0xFFFF);
	mPORTGSetPinsDigitalOut(0xFFFF);

  // Initialize the pins to all digital output and driven to ground.
  // Exception is RE7 and RE6 which are switch inputs
  PORTSetPinsDigitalIn(IOPORT_E, BIT_6);
  PORTSetPinsDigitalIn(IOPORT_E, BIT_7);

	mPORTAClearBits(0xFFFF);
	mPORTBClearBits(0xFFFF);
	mPORTCClearBits(0xFFFF);
	mPORTDClearBits(0xFFFF);
	mPORTEClearBits(0xFF3F);
	mPORTESetBits(0x000F);		// LED latches need to be set high for off
	mPORTFClearBits(0xFFFF);
	mPORTGClearBits(0xFFFF);

	INTEnableSystemMultiVectoredInt();
}
