#ifndef __SDCARD_MODULE
#define __SDCARD_MODULE

#include <base/GenericTypeDefs.h>
#include <usb/module.h>
#include <plib.h>
#include <sdcard\module.h>
#include <sdcard\diskio.h>
#include <sdcard\ff.h>
#include <userconfig.h>

// define the Processor instruction frequency
#define FOSC	80000000

// define the interface that the SD card is using
//#define MEDIASD_IF_SPI1
#define MEDIASD_SP2

// define the chip select pin function
#define _SetChipSelect(on)          {\
                                        mPORTGSetPinsDigitalOut(BIT_14);\
                                        if(on)\
                                            mPORTGClearBits(BIT_14);\
                                        else\
                                            mPORTGSetBits(BIT_14);\
                                    }

// Card detect - Read Only
#define SD_CD                   (mPORTGReadBits(BIT_12))             
#define SDSetCDDirection()      (mPORTGSetPinsDigitalIn(BIT_12))
// Write enable - Read Only
#define SD_WE                   (mPORTGReadBits(BIT_13))               
#define SDSetWEDirection()      (mPORTGSetPinsDigitalIn(BIT_13))

// SPI configuration defines
#define FATFS_SPI_START_CFG_1		(PRI_PRESCAL_64_1 | SEC_PRESCAL_8_1 | MASTER_ENABLE_ON | SPI_CKE_ON | SPI_SMP_ON)
#define FATFS_SPI_START_CFG_2		(SPI_ENABLE)

static BOOL cardInitialized;

void SDCARD_Initialize(void);
void SDCARD_Mount(void);
void SDCARD_Unmount(void);
void SDCARD_PrintDriveStatus(void);
void SDCARD_PrintDirectoryListing(void);

#endif