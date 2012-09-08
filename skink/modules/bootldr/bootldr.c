#include <bootldr/module.h>

/******************************************************************************
Global Variables
*******************************************************************************/
//FSFILE * myFile;
BYTE myData[512];
size_t numBytes;
UINT pointer = 0;
UINT readBytes;

UINT8 asciiBuffer[1024];
UINT8 asciiRec[200];
UINT8 hexRec[100];

T_REC record;

/****************************************************************************
Function prototypes
*****************************************************************************/
void ConvertAsciiToHex(UINT8* asciiRec, UINT8* hexRec);

void JumpToApp(void);
BOOL ValidAppPresent(void);

FW_VERSION GetNewestAvailableFirmwareVersion(void);
UINT8 FirmwareVersionCompare(FW_VERSION *left, FW_VERSION *right);
FW_VERSION GetCurrentFirmwareVersion(void);
void ExtractFirmwareVersionFromFilename(CHAR *filename, FW_VERSION *version);
BOOL ShouldFlashFirmware(CHAR *file, FW_VERSION *version);
BOOL NewerFirmwareExists(CHAR *file, FW_VERSION *version);
BOOL ForcedFirmwareExists(CHAR *file, FW_VERSION *version);


void BOOTLDR_Initialize(void (*errFunc)(void))
{
  ErrorFunction = errFunc;
  memset(&sTargetFile, 0, sizeof(sTargetFile));
}

void BOOTLDR_Run()
{
  volatile UINT i;
  FILEHANDLE *myFile;
  FILEHANDLE *currentFile;
  FW_VERSION newVersion;
  CHAR buffer[64];

  newVersion.major = 0;
  newVersion.minor = 0;
  newVersion.build = 0;

  //if(!ForcedFirmwareExists() && !NewerFirmwareExists() && ValidAppPresent())
  if(!ShouldFlashFirmware(sTargetFile, &newVersion) && ValidAppPresent())
  {
      // No new firmware to load. Jump
      // directly to the application
      JumpToApp();        
  }

  // At this point sTargetFile will have the name of the file we should use
  //strcpy(sTargetFile, "fw/force/v0_0_2.hex");      
	myFile = FATFS_fopen(sTargetFile,"r");
    
  if(myFile == NULL)// Make sure the file is present.
  {
    //Indicate error and stay in while loop.
      ErrorFunction();
  }     
  
  // Erase Flash (Block Erase the program Flash)
  EraseFlash();

  // Initialize the state-machine to read the records.
  record.status = REC_NOT_FOUND;
 
  while(1)
  {
   
     // For a faster read, read 512 bytes at a time and buffer it.
    readBytes = FATFS_fread((void *)&asciiBuffer[pointer], 1, 512, myFile);
    //readBytes = FSfread((void *)&asciiBuffer[pointer],1,512,myFile);
     
    if(readBytes == 0)
    {
      // Nothing to read. Come out of this loop
      // break;
      FATFS_fclose(myFile);
      // Something fishy. The hex file has ended abruptly, looks like there was no "end of hex record".
      //Indicate error and stay in while loop.
      ErrorFunction();       
    }

    for(i = 0; i < (readBytes + pointer); i ++)
    {
       
      // This state machine seperates-out the valid hex records from the read 512 bytes.
      switch(record.status)
      {
        case REC_FLASHED:
        case REC_NOT_FOUND:
          if(asciiBuffer[i] == ':')
          {
            // We have a record found in the 512 bytes of data in the buffer.
            record.start = &asciiBuffer[i];
            record.len = 0;
            record.status = REC_FOUND_BUT_NOT_FLASHED;
          }
          break;
        case REC_FOUND_BUT_NOT_FLASHED:
          if((asciiBuffer[i] == 0x0A) || (asciiBuffer[i] == 0xFF))
          {
            // We have got a complete record. (0x0A is new line feed and 0xFF is End of file)
            // Start the hex conversion from element
            // 1. This will discard the ':' which is
            // the start of the hex record.
            ConvertAsciiToHex(&record.start[1],hexRec);

            // We're done so let's close the file and update current.txt
            if(hexRec[3] == END_OF_FILE_RECORD)
            {
              FATFS_fclose(myFile);
              currentFile = FATFS_fopen("fw/current.txt", "wo");
              if(currentFile != NULL)
              {
                sprintf(buffer, "v%d_%d_%d.hex", newVersion.major, newVersion.minor, newVersion.build);
                FATFS_fwrite(buffer, 1, strlen(buffer), currentFile);
                FATFS_fclose(currentFile);
              }
            }

            WriteHexRecord2Flash(hexRec);
            record.status = REC_FLASHED;

            // Blink the green LED to indicate programming in progress
            mLED_Green_Toggle();
          }
          break;
      }
      // Move to next byte in the buffer.
      record.len ++;
    }

    if(record.status == REC_FOUND_BUT_NOT_FLASHED)
    {
      // We still have a half read record in the buffer. The next half part of the record is read 
      // when we read 512 bytes of data from the next file read. 
      memcpy(asciiBuffer, record.start, record.len);
      pointer = record.len;
      record.status = REC_NOT_FOUND;
    }
    else
    {
      pointer = 0;
    } 
  }//while(1)
  
}// end BOOTLDR_Run function

// ==================================================================
// BOOL ShouldFlashFirmware(CHAR *file, FW_VERSION *version)
// ==================================================================
// Description:   Determine if the bootloader module should update
//                the firmware.
//
// Precondition:  The SD card and file system must be initialized
//
// Input:         None
//
// Output:        TRUE if firmware is ready to load.  FALSE
//                otherwise.  file and version are also set
//                as part of this function.
//
// Side Effects:  None
// ==================================================================
BOOL ShouldFlashFirmware(CHAR *file, FW_VERSION *version)
{
  if(ForcedFirmwareExists(file, version))
    return TRUE;

  if(NewerFirmwareExists(file, version))
    return TRUE;

  return FALSE;
}

// ==================================================================
// BOOL NewerFirmwareExists(void)
// ==================================================================
// Description:   See if there is newer firmware to load
//
// Precondition:  The SD card and file system must be initialized
//
// Input:         None
//
// Output:        TRUE if newer firmware is ready to load.  FALSE
//                otherwise
//
// Side Effects:  None
// ==================================================================
BOOL NewerFirmwareExists(CHAR *file, FW_VERSION *version)
{
  FW_VERSION currentVersion, newestAvailable;
  currentVersion = GetCurrentFirmwareVersion();
  newestAvailable = GetNewestAvailableFirmwareVersion();
  if (FirmwareVersionCompare(&currentVersion, &newestAvailable) == RIGHT_VERSION_HIGHER)
  {
    sprintf(file, "fw/v%d_%d_%d.hex", newestAvailable.major, newestAvailable.minor, newestAvailable.build);
    version->major = newestAvailable.major;
    version->minor = newestAvailable.minor;
    version->build = newestAvailable.build;
    return TRUE;
  }
  
  return FALSE;
} 

// ==================================================================
// BOOL ForcedFirmwareExists(void)
// ==================================================================
// Description:   See if the user is trying to force a firmware
//                flash regardless of the existing version
//
// Precondition:  The SD card and file system must be initialized
//
// Input:         None
//
// Output:        TRUE if force firmware is ready to load.  FALSE
//                otherwise
//
// Side Effects:  None
// ==================================================================
BOOL ForcedFirmwareExists(CHAR *file, FW_VERSION *version)
{
  // A forced version, if it exists would be in /fw/force
  DIRECTORY *dir;
  FILEINFO *info;
  CHAR *temp;

  dir = FATFS_dopen("fw/force");
  if(dir != NULL)
  {
    info = FATFS_dgetnextfile(dir);
    if(info != NULL)
    {
      temp = FATFS_GetFileName(info);
      sprintf(file, "fw/force/%s", temp);
      ExtractFirmwareVersionFromFilename(temp, version);
      return TRUE;
    }
  }

  return FALSE;
}

FW_VERSION GetCurrentFirmwareVersion()
{
  FW_VERSION currentVersion;
  FILEHANDLE *currentFile;
  CHAR versionStr[32];
  currentVersion.build = 0;

  // The current version is found in /fw/current.txt
  currentFile = FATFS_fopen("fw/current.txt", "r");
  if(currentFile != NULL)
  {
    FATFS_fgets(versionStr, 32, currentFile);
    FATFS_fclose(currentFile);
    ExtractFirmwareVersionFromFilename(versionStr, &currentVersion);
  }
  else
  {
    // No current file exists so we'll assume no firmware is present yet
    currentVersion.minor = 0;
    currentVersion.major = 0;
  }

  return currentVersion;
}

FW_VERSION GetNewestAvailableFirmwareVersion()
{
  FW_VERSION newestVersion;
  FW_VERSION tempVersion;
  DIRECTORY *directory;
  FILEINFO *currentFileInfo;
  CHAR *fileName;
  newestVersion.major = 0;
  newestVersion.minor = 0;
  newestVersion.build = 0;

  // Loop through each file in fw folder and return the newest available
  directory = FATFS_dopen("fw");
  if(directory)
  {
    currentFileInfo = FATFS_dgetnextfile(directory);
    while(currentFileInfo != NULL)
    {
      fileName = FATFS_GetFileName(currentFileInfo);
      if(strcmp(fileName, "current.txt") != 0)
      {
        ExtractFirmwareVersionFromFilename(fileName, &tempVersion);
        if(FirmwareVersionCompare(&newestVersion, &tempVersion) == RIGHT_VERSION_HIGHER)
        {
          newestVersion.major = tempVersion.major;
          newestVersion.minor = tempVersion.minor;
          newestVersion.build = tempVersion.build;
        }
      }
      currentFileInfo = FATFS_dgetnextfile(directory);
    }
  }

  return newestVersion;
}

UINT8 FirmwareVersionCompare(FW_VERSION *left, FW_VERSION *right)
{
  if(left->major > right->major) return LEFT_VERSION_HIGHER;
  if(right->major> left->major) return RIGHT_VERSION_HIGHER;
  if(left->minor > right->minor) return LEFT_VERSION_HIGHER;
  if(right->minor > left->minor) return RIGHT_VERSION_HIGHER;
  if(left->build > right->build) return LEFT_VERSION_HIGHER;
  if(right->build > left->build) return RIGHT_VERSION_HIGHER;
  return SAME_VERSION;
}

void ExtractFirmwareVersionFromFilename(CHAR *filename, FW_VERSION *version)
{
  // Format of filename will be v1_3_1234.hex
  CHAR *token;
  token = strtok(filename, "v_.");
  version->major = atoi(token);
  token = strtok(NULL, "v_.");
  version->minor = atoi(token);
  token = strtok(NULL, "v_.");
  version->build = atoi(token);
}

/********************************************************************
* Function:   JumpToApp()
*
* Precondition: 
*
* Input:    None.
*
* Output:   
*
* Side Effects: No return from here.
*
* Overview:   Jumps to application.
*
*     
* Note:     None.
********************************************************************/
void JumpToApp(void)
{ 
  void (*fptr)(void);

  INTDisableInterrupts();

  fptr = (void (*)(void))USER_APP_RESET_ADDRESS;
  fptr();
} 



/********************************************************************
* Function:   ConvertAsciiToHex()
*
* Precondition: 
*
* Input:    Ascii buffer and hex buffer.
*
* Output:   
*
* Side Effects: No return from here.
*
* Overview:   Converts ASCII to Hex.
*
*     
* Note:     None.
********************************************************************/
void ConvertAsciiToHex(UINT8* asciiRec, UINT8* hexRec)
{
  UINT8 i = 0;
  UINT8 k = 0;
  UINT8 hex;
  
  
  while((asciiRec[i] >= 0x30) && (asciiRec[i] <= 0x66))
  {
    // Check if the ascci values are in alpha numeric range.
    
    if(asciiRec[i] < 0x3A)
    {
      // Numerical reperesentation in ASCII found.
      hex = asciiRec[i] & 0x0F;
    }
    else
    {
      // Alphabetical value.
      hex = 0x09 + (asciiRec[i] & 0x0F);            
    }
  
    // Following logic converts 2 bytes of ASCII to 1 byte of hex.
    k = i%2;
    
    if(k)
    {
      hexRec[i/2] |= hex;
      
    }
    else
    {
      hexRec[i/2] = (hex << 4) & 0xF0;
    } 
    i++;    
  }   
  
}
// Do not change this
#define FLASH_PAGE_SIZE 0x1000
/********************************************************************
* Function:   EraseFlash()
*
* Precondition: 
*
* Input:    None.
*
* Output:   
*
* Side Effects: No return from here.
*
* Overview:   Erases Flash (Block Erase).
*
*     
* Note:     None.
********************************************************************/
void EraseFlash(void)
{
  void * pFlash;
    UINT result;
    INT i;

    pFlash = (void*)APP_FLASH_BASE_ADDRESS;                 
    for( i = 0; i < ((APP_FLASH_END_ADDRESS - APP_FLASH_BASE_ADDRESS + 1)/FLASH_PAGE_SIZE); i++ )
    {
       result = NVMemErasePage( pFlash + (i*FLASH_PAGE_SIZE) );
        // Assert on NV error. This must be caught during debug phase.

        if(result != 0)
        {
           // We have a problem. This must be caught during the debug phase.
            while(1);
        } 
        // Blink LED to indicate erase is in progress.
        mLED_White_Toggle();
    }                      
}



/********************************************************************
* Function:   WriteHexRecord2Flash()
*
* Precondition: 
*
* Input:    None.
*
* Output:   
*
* Side Effects: No return from here.
*
* Overview:   Writes Hex Records to Flash.
*
*     
* Note:     None.
********************************************************************/
void WriteHexRecord2Flash(UINT8* HexRecord)
{
  static T_HEX_RECORD HexRecordSt;
  UINT8 Checksum = 0;
  UINT8 i;
  UINT WrData;
  UINT RdData;
  void* ProgAddress;
  UINT result;
    
  HexRecordSt.RecDataLen = HexRecord[0];
  HexRecordSt.RecType = HexRecord[3]; 
  HexRecordSt.Data = &HexRecord[4]; 
  
  // Hex Record checksum check.
  for(i = 0; i < HexRecordSt.RecDataLen + 5; i++)
  {
    Checksum += HexRecord[i];
  } 
  
    if(Checksum != 0)
    {
      //Error. Hex record Checksum mismatch.
      //Indicate Error by switching ON all LEDs.
      //Error();
      // Do not proceed further.
      ErrorFunction();
  } 
  else
  {
    // Hex record checksum OK.
    switch(HexRecordSt.RecType)
    {
      case DATA_RECORD:  //Record Type 00, data record.
        HexRecordSt.Address.byte.MB = 0;
          HexRecordSt.Address.byte.UB = 0;
          HexRecordSt.Address.byte.HB = HexRecord[1];
          HexRecordSt.Address.byte.LB = HexRecord[2];
          
          // Derive the address.
          HexRecordSt.Address.Val = HexRecordSt.Address.Val + HexRecordSt.ExtLinAddress.Val + HexRecordSt.ExtSegAddress.Val;
              
          while(HexRecordSt.RecDataLen) // Loop till all bytes are done.
          {
                      
            // Convert the Physical address to Virtual address. 
            ProgAddress = (void *)PA_TO_KVA0(HexRecordSt.Address.Val);
            
            // Make sure we are not writing boot area and device configuration bits.
            if(((ProgAddress >= (void *)APP_FLASH_BASE_ADDRESS) && (ProgAddress <= (void *)APP_FLASH_END_ADDRESS))
               && ((ProgAddress < (void*)DEV_CONFIG_REG_BASE_ADDRESS) || (ProgAddress > (void*)DEV_CONFIG_REG_END_ADDRESS)))
            {
              if(HexRecordSt.RecDataLen < 4)
              {
                
                // Sometimes record data length will not be in multiples of 4. Appending 0xFF will make sure that..
                // we don't write junk data in such cases.
                WrData = 0xFFFFFFFF;
                memcpy(&WrData, HexRecordSt.Data, HexRecordSt.RecDataLen);  
              }
              else
              { 
                memcpy(&WrData, HexRecordSt.Data, 4);
              }   
              // Write the data into flash. 
              result = NVMemWriteWord(ProgAddress, WrData); 
              // Assert on error. This must be caught during debug phase.   
              if(result != 0)
              {
                  while(1);
                }                 
            } 
            
            // Increment the address.
            HexRecordSt.Address.Val += 4;
            // Increment the data pointer.
            HexRecordSt.Data += 4;
            // Decrement data len.
            if(HexRecordSt.RecDataLen > 3)
            {
              HexRecordSt.RecDataLen -= 4;
            } 
            else
            {
              HexRecordSt.RecDataLen = 0;
            } 
          }
          break;
      
      case EXT_SEG_ADRS_RECORD:  // Record Type 02, defines 4th to 19th bits of the data address.
          HexRecordSt.ExtSegAddress.byte.MB = 0;
        HexRecordSt.ExtSegAddress.byte.UB = HexRecordSt.Data[0];
        HexRecordSt.ExtSegAddress.byte.HB = HexRecordSt.Data[1];
        HexRecordSt.ExtSegAddress.byte.LB = 0;
        // Reset linear address.
        HexRecordSt.ExtLinAddress.Val = 0;
        break;
        
      case EXT_LIN_ADRS_RECORD:   // Record Type 04, defines 16th to 31st bits of the data address. 
        HexRecordSt.ExtLinAddress.byte.MB = HexRecordSt.Data[0];
        HexRecordSt.ExtLinAddress.byte.UB = HexRecordSt.Data[1];
        HexRecordSt.ExtLinAddress.byte.HB = 0;
        HexRecordSt.ExtLinAddress.byte.LB = 0;
        // Reset segment address.
        HexRecordSt.ExtSegAddress.Val = 0;
        break;
        
      case END_OF_FILE_RECORD:  //Record Type 01, defines the end of file record.
        HexRecordSt.ExtSegAddress.Val = 0;
        HexRecordSt.ExtLinAddress.Val = 0;
        // Disable any interrupts here before jumping to the application.
        JumpToApp();
        break;
        
      default: 
        HexRecordSt.ExtSegAddress.Val = 0;
        HexRecordSt.ExtLinAddress.Val = 0;
        break;
    }   
  } 
    
} 

/********************************************************************
* Function:   ValidAppPresent()
*
* Precondition: 
*
* Input:    None.
*
* Output:   TRUE: If application is valid.
*
* Side Effects: None.
*
* Overview:   Logic: Check application vector has 
        some value other than "0xFFFFFF"
*
*     
* Note:     None.
********************************************************************/
BOOL ValidAppPresent(void)
{
  volatile UINT32 *AppPtr;
  
  AppPtr = (UINT32*)USER_APP_RESET_ADDRESS;

  if(*AppPtr == 0xFFFFFFFF)
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}