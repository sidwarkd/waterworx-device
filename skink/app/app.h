#ifndef APP_H
#define APP_H

#include <xc.h>
#include <plib.h>
#include "userconfig.h"
#include <string.h>

void InitializeSystem();

// Modules
#include <base/module.h>
#include <delay/module.h>
#include <mdd/module.h>
#include <bootldr/module.h>
//#include <crystalfontz/module.h>
//#include <wifi/module.h>
//#include <json/module.h>
//#include <usb/module.h>
//#include <sdcard/module.h>
//#include <rtcc/module.h>

// =============================================
// CONTENTS OF SD_BOOTLOADER.H
// =============================================

#define REC_FLASHED 0
#define REC_NOT_FOUND 1
#define REC_FOUND_BUT_NOT_FLASHED 2

//#include "GenericTypeDefs.h"


typedef struct
{
    UINT8 *start;
    UINT8 len;
    UINT8 status;
}T_REC;

typedef struct 
{
	UINT8 RecDataLen;
	DWORD_VAL Address;
	UINT8 RecType;
	UINT8* Data;
	UINT8 CheckSum;	
	DWORD_VAL ExtSegAddress;
	DWORD_VAL ExtLinAddress;
}T_HEX_RECORD;	


#define DATA_RECORD 		0
#define END_OF_FILE_RECORD 	1
#define EXT_SEG_ADRS_RECORD 2
#define EXT_LIN_ADRS_RECORD 4

void ConverAsciiToHex(UINT8* asciiRec, UINT8* hexRec);
void EraseFlash(void);
void WriteHexRecord2Flash(UINT8* HexRecord);

// =============================================
// END CONTENTS OF SD_BOOTLOADER.H
// =============================================


#ifdef TESTING
//#include <test/module.h>
#endif

#endif
