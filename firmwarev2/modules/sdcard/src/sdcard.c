#include <sdcard/module.h>

///////////////////////////////////////////////////////////////////
// local functions
//static FRESULT scan_files (char* path);

///////////////////////////////////////////////////////////////////

void SDCARD_Initialize(void)
{
	// Set up Timer 1 to generate interrupts at 1kHz
	// this is used to drive the underlying disk io system
 	OpenCoreTimer(FOSC/ 2000);
 	// set up the timer interrupt with a priority of 1
 	mConfigIntCoreTimer(CT_INT_ON | CT_INT_PRIOR_1);

	_SetChipSelect(FALSE);
	fsMounted = FALSE;

#if _USE_LFN
	_currentFileInfo.lfname = lfn;
  _currentFileInfo.lfsize = sizeof(lfn);
#endif

	// Setup the I/O
  SDSetCDDirection();     // CD as input
  SDSetWEDirection();     // WE as input

	//SDCARD_Mount();
}

BOOL SDCARD_Mount(void)
{
	FRESULT res;
	if(fsMounted == FALSE)
	{
		if (!(disk_status(MMC_DRIVE) & STA_NODISK)) {
			// disk inserted so initialise it
			if (disk_initialize(MMC_DRIVE) == 0) {
				res = f_mount(MMC_DRIVE, &fatfs[MMC_DRIVE]);
				if (res == FR_OK) {
					fsMounted = TRUE;
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return TRUE;
	}
}

void SDCARD_Unmount(void)
{
	f_mount(MMC_DRIVE, NULL);
	mDisableIntCoreTimer();
}


/*********************************************************************
 * Function:  		void T1Handler(void)     
 *
 * PreCondition:    
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    
 *
 * Overview:        FatFs requires a 1ms tick timer to aid
 *					with low level function timinng
 *
 * Note:           
 ********************************************************************/
void __attribute__((interrupt(ipl1), vector(_CORE_TIMER_VECTOR))) T1Handler(void)
{
	//static const BYTE dom[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	//static int div1k;
	//BYTE n;
	
	// clear the interrupt flag
	mCTClearIntFlag();
	OpenCoreTimer(FOSC/2000);
	//Timer++;

	disk_timerproc();	// call the low level disk IO timer functions
}


/*********************************************************************
 * Function:  		DWORD get_fattime(void)
 *
 * PreCondition:    
 *
 * Input:           None
 *
 * Output:          Time
 *
 * Side Effects:    
 *
 * Overview:        when writing fatfs requires a time stamp
 *					in this exmaple we are going to use a counter
 *					If the starter kit has the 32kHz crystal
 *					installed then the RTCC could be used instead
 *
 * Note:           
 ********************************************************************/
DWORD get_fattime(void)
{
	DWORD tmr;

	INTDisableInterrupts();
	tmr = GetCurrentDateTimeAsDWORD();
	INTEnableInterrupts();

	return tmr;
}

