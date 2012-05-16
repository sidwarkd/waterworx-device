/******************************************************************************
 *
 *              DISKIO WEAK FUNCTIONS
 *
 ******************************************************************************
 * FileName:        fatfs_mmc_usb_ata_weak.c
 * Dependencies:    See include below
 * Processor:       PIC32
 * Compiler:        C32 V1.03
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * It is 
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
 * 11/26/08	V1.00 S Justice		First version of fatfs sd card support
 *								Implements abstration layer
 *
 *****************************************************************************/
#ifdef _DISKIO_WEAK
#include <sdcard\diskio.h>
#include <plib.h>

static volatile DSTATUS Stat = STA_NOINIT;

/******************************************************************************
 * Function:        DSTATUS <xxx>_disk_initialize(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Status after init
 *
 * Side Effects:    None
 *
 * Overview:        Function to initialize the Media called during mount
 *
 * Note:            None
 *****************************************************************************/
DSTATUS __attribute__((weak)) ATA_disk_initialize(void)
{ 
	return Stat;
}  
DSTATUS __attribute__((weak)) MMC_disk_initialize(void)
{ 
	return Stat;
}  
DSTATUS __attribute__((weak)) USB_disk_initialize(void)
{ 
	return Stat;
}  
/******************************************************************************
 * Function:        DSTATUS <xxx>_disk_status(void)
 *
 * PreCondition:    None
 *
 * Input:           drv - Physical drive number
 *
 * Output:          Status of drive
 *
 * Side Effects:    None
 *
 * Overview:        Function to return status of drive
 *
 * Note:            None
 *****************************************************************************/
DSTATUS __attribute__((weak)) ATA_disk_status(void)
{
	return Stat;	
}
DSTATUS __attribute__((weak)) MMC_disk_status(void)
{
	return Stat;	
}
DSTATUS __attribute__((weak)) USB_disk_status(void)
{
	return Stat;	
}
/******************************************************************************
 * Function:        DRESULT <xxx>_disk_read(BYTE *buff,
 *									  DWORD sector,
 *									  BYTE count)
 *
 * PreCondition:    None
 *
 * Input:           buff - pointer to the data buffer to store read data
 *					sector - start sector number (LBA)
 *					count - sector count (1..255)
 *
 * Output:          Status of read
 *
 * Side Effects:    None
 *
 * Overview:        Function to read a specific sector on the media.
 *
 * Note:            None
 *****************************************************************************/
DRESULT __attribute__((weak)) ATA_disk_read(BYTE *buff, DWORD sector, BYTE count)
{
	return RES_NOTRDY;
}  
DRESULT __attribute__((weak)) MMC_disk_read(BYTE *buff, DWORD sector, BYTE count)
{
	return RES_NOTRDY;
}  
DRESULT __attribute__((weak)) USB_disk_read(BYTE *buff, DWORD sector, BYTE count)
{
	return RES_NOTRDY;
}  

/******************************************************************************
 * Function:        DRESULT <xxx>_disk_write(const BYTE *buff,
 *									   DWORD sector,
 *									   BYTE count)
 *
 * PreCondition:    None
 *
 * Input:           buff - Pointer to the data to be written
 *					sector - Start sector number (LBA)
 *					count - Sector count (1..255)
 *
 * Output:          Status of write
 *
 * Side Effects:    None
 *
 * Overview:        Function to write a specific sector on the media.
 *
 * Note:            None
 *****************************************************************************/
#if _READONLY == 0
DRESULT __attribute__((weak)) ATA_disk_write(const BYTE *buff, DWORD sector, BYTE count)
{
	return RES_NOTRDY;   
}
DRESULT __attribute__((weak)) MMC_disk_write(const BYTE *buff, DWORD sector, BYTE count)
{
	return RES_NOTRDY;   
}
DRESULT __attribute__((weak)) USB_disk_write(const BYTE *buff, DWORD sector, BYTE count)
{
	return RES_NOTRDY;   
}
#endif

/******************************************************************************
 * Function:        DRESULT <xxx>_disk_ioctl(BYTE ctrl, void* buff)
 *
 * PreCondition:    None
 *
 * Input:           ctrl - control code
 *					buff - buffer to send/receive data block
 *
 * Output:          Success/Failure
 *
 * Side Effects:    None
 *
 * Overview:        Perform miscellaneous control functions
 *
 * Note:            None
 *****************************************************************************/
DRESULT __attribute__((weak)) ATA_disk_ioctl(BYTE ctrl, void* buff)
{
	return RES_NOTRDY;
}
DRESULT __attribute__((weak)) MMC_disk_ioctl(BYTE ctrl, void* buff)
{
	return RES_NOTRDY;
}
DRESULT __attribute__((weak)) USB_disk_ioctl(BYTE ctrl, void* buff)
{
	return RES_NOTRDY;
}
#endif
