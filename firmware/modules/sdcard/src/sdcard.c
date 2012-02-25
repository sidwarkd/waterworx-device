/******************************************************************************
 *
 *              Main Demonstration of fatfs on PIC32 Starter Kit
 *
 ******************************************************************************
 * FileName:        main.c
 * Dependencies:    See include below
 * Processor:       PIC32
 * Compiler:        C32 V1.03
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * Microchip Technology Incorporated ("Microchip) and its licensors retain 
 * all ownership and intellectual property rights in the code accompanying 
 * this message and in all derivatives thereto.  The code and information 
 * accompanying this message is provided for your convenience and use with 
 * Microchip products only.  Your acceptance and/or use of this code 
 * constitute agreement to the terms and conditions of this notice.Microchip 
 * disclaims all liability arising from this information and its use.  It is 
 * your responsibility to ensure that your application meets with your 
 * specifications.Further, the implementation and use of the FAT file system 
 * accompanying this code, SD card specifications, MMC card specifications 
 * and other third party tools may require a license from various entities, 
 * including, but not limited to Microsoft® Corporation, SD Card Association 
 * and MMCA.  It is your responsibility to obtain more information regarding 
 * any applicable licensing obligations.
 * 
 * CODE AND INFORMATION ACCOMPANYING THIS MESSAGE IS PROVIDED “AS IS.”  
 * MICROCHIP AND ITS LICENSORS MAKES NO REPRESENTATION OR WARRANTIES OF ANY 
 * KIND WHETHER EXPRESS OR IMPLIED, WRITTEN OR ORAL, STATUTORY OR OTHERWISE, 
 * RELATED TO THE INFORMATION PROVIDED TO YOU, INCLUDING BUT NOT LIMITED TO 
 * ITS CONDITION, QUALITY, PERFORMANCE, MERCHANTABILITY, NON-INFRINGEMENT, 
 * OR FITNESS FOR PURPOSE.  MICROCHIP AND ITS LICENSORS ARE NOT LIABLE, UNDER 
 * ANY CIRCUMSTANCES, FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES, 
 * FOR ANY REASON WHATSOEVER.  	 
 *
 *****************************************************************************
 *
 * 11/17/08	V1.00 D.Wenn		First version, designed for PIC32 Starter Kit
 * 11/25/08 V1.01 D.Wenn		Added PIC32 image output
 *
 *****************************************************************************/

#include <sdcard/module.h>

//configure the hardware
//#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
//#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1


///////////////////////////////////////////////////////////////////
// local variables
//volatile BYTE rtcYear = 108, rtcMon = 11, rtcMday = 17;	// RTC starting values
//volatile BYTE rtcHour = 12, rtcMin, rtcSec;
//volatile BYTE tick;			// crude state machine pace control
DWORD acc_size;				/* Work register for fs command */
WORD acc_files, acc_dirs;
FILINFO finfo;

FATFS fatfs[_DRIVES];	// file system object
BYTE buff[1024];		// working buffer
//volatile UINT Timer;		/* 1kHz increment timer */


///////////////////////////////////////////////////////////////////
// local functions
static FRESULT scan_files (char* path);

///////////////////////////////////////////////////////////////////

void SDCARD_Initialize(void)
{
	// Set up Timer 1 to generate interrupts at 1kHz
	// this is used to drive the underlying disk io system
  OpenCoreTimer(FOSC/ 2000);
  // set up the timer interrupt with a priority of 1
  mConfigIntCoreTimer(CT_INT_ON | CT_INT_PRIOR_1);

	_SetChipSelect(FALSE);
	cardInitialized = FALSE;

	SDCARD_Mount();
}

void SDCARD_Mount(void)
{
	if (!(disk_status(MMC_DRIVE) & STA_NODISK)) {
		// disk inserted so initialise it
		if (disk_initialize(MMC_DRIVE) == 0) {
			if (f_mount(MMC_DRIVE, &fatfs[MMC_DRIVE]) == FR_OK) {
				cardInitialized = TRUE;
			}	
		}
	}
}

void SDCARD_Unmount(void)
{
	f_mount(MMC_DRIVE, NULL);
	mDisableIntCoreTimer();
}

void SDCARD_PrintDriveStatus(void){
	FATFS *fs;
	char printBuffer[512];
	DWORD param1;
	BYTE res;

	if(!cardInitialized)
	{
		if (!(disk_status(MMC_DRIVE) & STA_NODISK)) {
			// disk inserted so initialise it
			if (disk_initialize(MMC_DRIVE) == 0) {
				if (f_mount(MMC_DRIVE, &fatfs[MMC_DRIVE]) == FR_OK) {
					SERIALUSB_Write("Disk initialized and mounted\n");
					cardInitialized = TRUE;
				}	
			}
		}
	}
	else
	{
		strcpy(buff, "1:");
		res = f_getfree(buff, &param1, &fs);
		if (res == FR_OK){
			sprintf(printBuffer,"\rFAT type = %u\rBytes/Cluster = %lu\rNumber of FATs = %u\r"
					"Root DIR entries = %u\rSectors/FAT = %lu\r"
					"Number of clusters = %lu\n",
					(WORD)fs->fs_type, (DWORD)fs->csize * 512, (WORD)fs->n_fats,
					fs->n_rootdir, fs->sects_fat, (DWORD)fs->max_clust - 2);
			SERIALUSB_Write(printBuffer);
			sprintf(printBuffer,"\rFAT start (lba) = %lu\rDIR start (lba,clustor) = %lu\r"
					"Data start (lba) = %lu\n",
					fs->fatbase, fs->dirbase, fs->database);
			SERIALUSB_Write(printBuffer);
		}
		
		acc_size = acc_files = acc_dirs = 0;
		res = scan_files(buff);
		if (res == FR_OK) { 
			sprintf(printBuffer,"\r%u files, %lu bytes.\r%u folders.\r"
					"%lu KB total disk space.\r%lu KB available.\n",
					acc_files, acc_size, acc_dirs,
					(fs->max_clust - 2) * (fs->csize / 2), 
					param1 * (fs->csize / 2));
			SERIALUSB_Write(printBuffer);
		}
	}
}

void SDCARD_PrintDirectoryListing(void)
{
	DIR dir;
	DWORD param1, s1, s2;
	BYTE res;
	char printBuffer[256];

	if(!cardInitialized)
	{
		if (!(disk_status(MMC_DRIVE) & STA_NODISK)) {
			// disk inserted so initialise it
			if (disk_initialize(MMC_DRIVE) == 0) {
				if (f_mount(MMC_DRIVE, &fatfs[MMC_DRIVE]) == FR_OK) {
					SERIALUSB_Write("Disk initialized and mounted\n");
					cardInitialized = TRUE;
				}	
			}
		}
		else
		{
			SERIALUSB_Write("Still not connected");
		}
	}
	else
	{
		strcpy(buff, "1:");
		res = f_opendir(&dir, buff);
		if (res == FR_OK) {
			param1 = s1 = s2 = 0;	
			
			while (1) {
				res = f_readdir(&dir, &finfo);	
				if ((res != FR_OK) || (!finfo.fname[0])) 
					break;
				if (finfo.fattrib & AM_DIR) {
					s2++;
				} else {
					s1++;
					param1 += finfo.fsize;
				}
				
				sprintf(printBuffer,"%c%c%c%c%c %u/%02u/%02u %02u:%02u %9lu  %s\n", 
						(finfo.fattrib & AM_DIR) ? 'D' : '-',
						(finfo.fattrib & AM_RDO) ? 'R' : '-',
						(finfo.fattrib & AM_HID) ? 'H' : '-',
						(finfo.fattrib & AM_SYS) ? 'S' : '-',
						(finfo.fattrib & AM_ARC) ? 'A' : '-',
						(finfo.fdate >> 9) + 1980, (finfo.fdate >> 5) & 15, finfo.fdate & 31,
						(finfo.ftime >> 11), (finfo.ftime >> 5) & 63,
						finfo.fsize, &(finfo.fname[0]));
				SERIALUSB_Write(printBuffer);	
				SERIALUSB_ProcessTasks();
			}		
			sprintf(printBuffer,"%4u File(s),%10lu bytes total\r%4u Dir(s)\n", s1, param1, s2);		
			SERIALUSB_Write(printBuffer);	
			//DBPRINTF("%4u File(s),%10lu bytes total\r%4u Dir(s)\n", s1, param1, s2);
		}	
	}
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
	/*tmr =	  (((DWORD)rtcYear - 80) << 25)
			| ((DWORD)rtcMon << 21)
			| ((DWORD)rtcMday << 16)
			| (WORD)(rtcHour << 11)
			| (WORD)(rtcMin << 5)
			| (WORD)(rtcSec >> 1);*/
	tmr = GetCurrentDateTimeAsDWORD();
	INTEnableInterrupts();

	return tmr;
}

///////////////////////////////////////////////////////////////////
// scan files in a given path for type information
static FRESULT scan_files(char* path)
{
	DIR dirs;
	FRESULT res;
	BYTE i;

	if ((res = f_opendir(&dirs, path)) == FR_OK) {
		i = strlen(path);
		while (((res = f_readdir(&dirs, &finfo)) == FR_OK) && finfo.fname[0]) {
			if (finfo.fattrib & AM_DIR) {
				acc_dirs++;
				*(path+i) = '/'; strcpy(path+i+1, &finfo.fname[0]);
				res = scan_files(path);
				*(path+i) = '\0';
				if (res != FR_OK) break;
			} else {
				acc_files++;
				acc_size += finfo.fsize;
			}
		}
	}
	return res;
}

