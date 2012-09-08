#ifndef __SDCARD_MODULE
#define __SDCARD_MODULE

#include <plib.h>
#include <base/GenericTypeDefs.h>
#include <sdcard\module.h>
#include <sdcard\diskio.h>
#include <sdcard\ff.h>
#include <userconfig.h>


// Make sure everything we need is defined in userconfig.h
#if !defined(MEDIASD_IF_SPI1) && !defined(MEDIASD_SP2)
	#error You must specify an SPI mode to use.  Current options are MEDIASD_IF_SPI1 and MEDIASD_SP2
#endif

#if !defined(SD_CD)
	#error Could not find definition of SD_CD.  This is a macro to get the status of card detect.  For example (mPORTGReadBits(BIT_12))
#endif

#if !defined(SDSetCDDirection)
	#error Could not find definition of SDSetCDDirection.  This is a macro to configure the IO pin for card detect.  For example (PORTSetPinsDigitalIn(IOPORT_G, BIT_12)) 
#endif

#if !defined(SD_WE)
	#error Could not find definition of SD_WE.  This is a macro to get the status of write protect.  For example (mPORTGReadBits(BIT_12))
#endif

#if !defined(SDSetWEDirection)
	#error Could not find definition of SDSetWEDirection.  This is a macro to configure the IO pin for write protect.  or example (PORTSetPinsDigitalIn(IOPORT_G, BIT_12)) 
#endif

#if !defined(_SetChipSelect)
	#error Could not find definition of _SetChipSelect.  This is a macro to set the state of the IO pin for the SD card chip select.
#endif

#if !defined(FATFS_SPI_START_CFG_1)
	#error Could not find definition of FATFS_SPI_START_CFG_1.  This is part of how you want the SPI peripheral configured on the PIC
#endif

#if !defined(FATFS_SPI_START_CFG_2)
	#error Could not find definition of FATFS_SPI_START_CFG_2.  This is part of how you want the SPI peripheral configured on the PIC
#endif


// define the Processor instruction frequency
// Reuse the setting in userconfig.h
#define FOSC	CLOCK_FREQ

typedef FIL     FILEHANDLE;
typedef FILINFO FILEINFO;
typedef DIR     DIRECTORY;

#define FATFS_fsize(fp) ((fp)->fsize)

// Helper functions for interacting with the SD card
//BOOL OpenFile(char *filename, FILEHANDLE *stream, BYTE flags);
//void CloseFile(FILEHANDLE *stream);
//int WriteFile(const char *str, FILEHANDLE *stream);
//BOOL DirectoryExists(char *dir);
//BOOL OpenDirectory(char *directory, DIRECTORY *directory);
//BOOL GetNextFile(DIRECTORY *directory, char *filename);
//int ReadFile(void *buffer, int numBytesToRead, FILEHANDLE *file);

// =================================
// INTERNAL MODULE FUNCTIONS/MEMBERS
// =================================

extern BOOL fsMounted;
extern FATFS fatfs[2];  // file system object
extern FATFS *fs;

extern DIRECTORY _currentDirectory;
extern FILEINFO _currentFileInfo;
//extern FILEHANDLE _currentFile;
extern UINT8 numOpenFiles;

#if _USE_LFN
extern char lfn[_MAX_LFN + 1];
#endif


// =================================
// API FUNCTIONS INTO THIS MODULE
// =================================
void SDCARD_Initialize(void);
BOOL SDCARD_Mount(void);
void SDCARD_Unmount(void);
BOOL SDCARD_IsCardInserted(void);

void FATFS_fclose(FILEHANDLE *file);
CHAR FATFS_fgetc(FILEHANDLE *file);
CHAR* FATFS_fgets(CHAR *str, int num, FILEHANDLE *file);
FILEHANDLE* FATFS_fopen(CHAR *filename, CHAR *mode);
void FATFS_fputc(CHAR character, FILEHANDLE *file);
void FATFS_fputs(CHAR *str, FILEHANDLE *file);
size_t FATFS_fread(void *buffer, size_t size, size_t count, FILEHANDLE *file);
size_t FATFS_fwrite(void *buffer, size_t size, size_t count, FILEHANDLE *file);
BOOL FATFS_feof(FILEHANDLE *file);

DIRECTORY* FATFS_dopen(CHAR *directory);
FILEINFO* FATFS_dgetnextfile(DIRECTORY *directory);
BOOL FATFS_DirectoryExists(CHAR *directory);
CHAR* FATFS_GetFileName(FILEINFO *fileInfo);

#endif