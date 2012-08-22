#define APPLICATION_ENTRY_POINT

#include "app.h"

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

  // Wait for an SD card to be inserted
  while(!SDCARD_IsCardInserted())
  {
    mLED_Green_Toggle();
    DelayMs(200);
  }

  // Some SD card sockets trigger the card detect long before the card is
  // actually seated in the socket.  Let's give ourselves some time here
  mLED_Green_On();
  DelayMs(2000);

  if(!SDCARD_Mount())
  {
    // Something went wrong with the SD card.  We can't go any further
    Error();
  }

  // Set up the bootloader module to use our custom error function
  BOOTLDR_Initialize(&Error);
  BOOTLDR_Run();

  // We should never get to the next line of code but just in case let's 
  // make that an error case
  Error();
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
	
  // Handle module initializations
	SDCARD_Initialize();
}

void Error()
{
  while(1)
  {
    mLED_Red_Toggle();
    DelayMs(200);
  }
}
