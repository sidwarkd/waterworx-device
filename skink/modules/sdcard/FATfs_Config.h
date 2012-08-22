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
 *--------------------------------------------------------------------------/
 * FatFs - FAT file system module include file  R0.06        (C)ChaN, 2008
 * --------------------------------------------------------------------------/
 * FatFs module is an experimenal project to implement FAT file system to
 * cheap microcontrollers. This is a free software and is opened for education,
 * research and development under license policy of following trems.
 *
 * Copyright (C) 2008, ChaN, all right reserved.
 *
 * The FatFs module is a free software and there is no warranty.
 * You can use, modify and/or redistribute it for personal, non-profit or
   commercial use without any restriction under your responsibility.
 * Redistributions of source code must retain the above copyright notice.
 *
 * ---------------------------------------------------------------------------
 *
 *****************************************************************************
 *
 * 11/17/08	V1.00 D.Wenn		First version, designed for PIC32 Starter Kit
 * 11/25/08 V1.01 D.Wenn		Added PIC32 image output
 *
 *****************************************************************************/

#ifndef _FATFS_CONFIG
#define _FATFS_CONFIG


/* Setting _FS_READONLY to 1 defines read only configuration. This removes
/  writing functions, f_write, f_sync, f_unlink, f_mkdir, f_chmod, f_rename,
/  f_truncate and useless f_getfree. */
#define _FS_READONLY	    1

/* The _FS_MINIMIZE option defines minimization level to remove some functions.
/  0: Full function.
/  1: f_stat, f_getfree, f_unlink, f_mkdir, f_chmod, f_truncate and f_rename are removed.
/  2: f_opendir and f_readdir are removed in addition to level 1.
/  3: f_lseek is removed in addition to level 2. */
#define _FS_MINIMIZE	    1

/* To enable string functions, set _USE_STRFUNC to 1 or 2. */
#define	_USE_STRFUNC	    0

/* When _USE_MKFS is set to 1 and _FS_READONLY is set to 0, f_mkfs function is
/  enabled. */
#define	_USE_MKFS	        1

/* Number of logical drives to be used. This affects the size of internal table. */
#define _DRIVES		        2

/* When _MULTI_PARTITION is set to 0, each logical drive is bound to same
/  physical drive number and can mount only 1st primaly partition. When it is
/  set to 1, each logical drive can mount a partition listed in Drives[]. */
#define	_MULTI_PARTITION	0

/* To enable FSInfo support on FAT32 volume, set _USE_FSINFO to 1. */
#define _USE_FSINFO	        0

/* When _USE_SJIS is set to 1, Shift-JIS code transparency is enabled, otherwise
/  only US-ASCII(7bit) code can be accepted as file/directory name. */
#define	_USE_SJIS	        1

/* When _USE_NTFLAG is set to 1, upper/lower case of the file name is preserved.
/  Note that the files are always accessed in case insensitive. */
#define	_USE_NTFLAG	        1



#endif
