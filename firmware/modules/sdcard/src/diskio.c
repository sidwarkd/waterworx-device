/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include <sdcard\diskio.h>
#define _DISKIO_WEAK
#include <sdcard\diskio_weak.h>


/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	DSTATUS stat;
	int result;

	switch (drv) {
	case ATA_DRIVE :
		result = ATA_disk_initialize();
		// translate the result code here
		stat = result;
		return stat;

	case MMC_DRIVE :
		result = MMC_disk_initialize();
		// translate the reslut code here
		stat = result;
		return stat;

	case USB_DRIVE :
		result = USB_disk_initialize();
		// translate the reslut code here
		stat = result;
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	DSTATUS stat;
	int result;

	switch (drv) {
	case ATA_DRIVE :
		result = ATA_disk_status();
		// translate the reslut code here
		stat = result;
		return stat;

	case MMC_DRIVE :
		result = MMC_disk_status();
		// translate the reslut code here
		stat = result;
		return stat;

	case USB_DRIVE :
		result = USB_disk_status();
		// translate the reslut code here
		stat = result;
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	DRESULT res;
	int result;

	switch (drv) {
	case ATA_DRIVE :
		result = ATA_disk_read(buff, sector, count);
		// translate the reslut code here
		res = result;
		return res;

	case MMC_DRIVE :
		result = MMC_disk_read(buff, sector, count);
		// translate the reslut code here
		res = result;
		return res;

	case USB_DRIVE :
		result = USB_disk_read(buff, sector, count);
		// translate the reslut code here
		res = result;
		return res;
	}
	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	DRESULT res;
	int result;

	switch (drv) {
	case ATA_DRIVE :
		result = ATA_disk_write(buff, sector, count);
		// translate the reslut code here
		res = result;
		return res;

	case MMC_DRIVE :
		result = MMC_disk_write(buff, sector, count);
		// translate the reslut code here
		res = result;
		return res;

	case USB_DRIVE :
		result = USB_disk_write(buff, sector, count);
		// translate the reslut code here
		res = result;
		return res;
	}
	return RES_PARERR;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (drv) {
	case ATA_DRIVE :
		// pre-process here

		result = ATA_disk_ioctl(ctrl, buff);
		// post-process here
		res = result;
		return res;

	case MMC_DRIVE :
		// pre-process here

		result = MMC_disk_ioctl(ctrl, buff);
		// post-process here
		res = result;
		return res;

	case USB_DRIVE :
		// pre-process here

		result = USB_disk_ioctl(ctrl, buff);
		// post-process here
		res = result;
		return res;
	}
	return RES_PARERR;
}

