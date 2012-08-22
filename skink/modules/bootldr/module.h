#ifndef BOOTLDR_MODULE_H
#define BOOTLDR_MODULE_H

#include <userconfig.h>
#include <bootldr/NVMem.h>
#include <bootldr/Bootloader.h>

// =================================
// MODULE DEPENDENCIES
// =================================
#include <sdcard/module.h>
#include <delay/module.h>

#define AUX_FLASH_BASE_ADRS       (0x7FC000)
#define AUX_FLASH_END_ADRS        (0x7FFFFF)
#define DEV_CONFIG_REG_BASE_ADDRESS   (0xF80000)
#define DEV_CONFIG_REG_END_ADDRESS    (0xF80012)

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


#define DATA_RECORD     0
#define END_OF_FILE_RECORD  1
#define EXT_SEG_ADRS_RECORD 2
#define EXT_LIN_ADRS_RECORD 4

void ConverAsciiToHex(UINT8* asciiRec, UINT8* hexRec);
void EraseFlash(void);
void WriteHexRecord2Flash(UINT8* HexRecord);

// =============================================
// END CONTENTS OF SD_BOOTLOADER.H
// =============================================

// =================================
// INTERNAL MODULE FUNCTIONS/MEMBERS
// =================================
void (*ErrorFunction)(void);
char sTargetFile[64];

// =================================
// API FUNCTIONS INTO THIS MODULE
// =================================
void BOOTLDR_Initialize(void (*errFunc)(void));
void BOOTLDR_Run(void);

#endif