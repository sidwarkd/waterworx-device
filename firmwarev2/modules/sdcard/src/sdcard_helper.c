#include <sdcard/module.h>


/*BOOL OpenFile(char *filename, FILEHANDLE *stream, BYTE flags)
{
	FRESULT res;
	char buffer[16];
	char fatfsFilename[32];
	sprintf(&fatfsFilename[0], "1:%s", filename);
	if(fsMounted == TRUE)
	{
		res = f_open((FIL*)stream, &fatfsFilename[0], flags);
		if(res == FR_OK)
		{
			f_lseek((FIL*)stream, f_size(stream));
			return TRUE;
		}
		else
		{
			sprintf(&buffer[0], "Result: %d", res);
			//SERIALUSB_Write(&fatfsFilename[0]);
		}
	}
	else
	{
		//SERIALUSB_Write("FS not mounted");
	}
	return FALSE;
}

void CloseFile(FILEHANDLE *stream)
{
	if(fsMounted)
	{
		f_close((FIL*)stream);
	}
}

#if (_FS_READONLY != 1)
int WriteFile(const char *str, FILEHANDLE *stream)
{
	UINT numBytesWritten = 0;
	if(fsMounted)
	{
		f_write((FIL*)stream, str, strlen(str), &numBytesWritten);
		return numBytesWritten;
	}
	return -1;
}
#endif


BOOL DirectoryExists(char *dir)
{
	DIRECTORY directory;
	char buffer[64];
	sprintf(&buffer[0], "1:%s", dir);
	if(f_opendir(&directory, buffer) == FR_OK)
	{
		return TRUE;
	} 
	return FALSE;
}*/


BOOL SDCARD_IsCardInserted()
{
	if(SD_CD != 0)
		return FALSE;
	else
		return TRUE;
}

void FATFS_fclose(FILEHANDLE *file)
{
	if(fsMounted)
	{
		f_close((FIL*)file);
	}
}

CHAR FATFS_fgetc(FILEHANDLE *file)
{
	CHAR c;
	FATFS_fread(&c, 1, 1, file);
	return c;
}

CHAR* FATFS_fgets(CHAR *str, int num, FILEHANDLE *file)
{
	int bytesRead = 0;
	bytesRead = FATFS_fread(str, 1, num, file);
	str[bytesRead] = '\0';
	return str;
}

FILEHANDLE* FATFS_fopen(CHAR *filename, CHAR *mode)
{
	FRESULT res;
	BYTE flags;
	char fatfsFilename[64];
	flags = 0;
	sprintf(&fatfsFilename[0], "1:%s", filename);
	if(fsMounted == TRUE)
	{
		// Set the flags based on mode passed in
		if(strchr(mode, 'r') != NULL) flags |= FA_READ;
		#if !_FS_READONLY
		if(strchr(mode, 'w') != NULL) flags |= FA_WRITE;
		if(strchr(mode, 'c') != NULL) flags |= FA_OPEN_ALWAYS;
		if(strchr(mode, 'n') != NULL) flags |= FA_CREATE_NEW;
		if(strchr(mode, 'o') != NULL) flags |= FA_CREATE_ALWAYS;
		#endif


		res = f_open((FIL*)&_currentFile, &fatfsFilename[0], flags);
		if(res == FR_OK)
		{
			f_lseek(&_currentFile, 0);
			return &_currentFile;
		}
	}

	return NULL;
}

size_t FATFS_fread(void *buffer, size_t size, size_t count, FILEHANDLE *file)
{
	UINT numBytesRead = 0;
	if(fsMounted)
	{
		f_read((FIL*)file, buffer, size * count, &numBytesRead);
		return (size_t)numBytesRead;
	}
	return 0;
}

#if (_FS_READONLY < 1)
size_t FATFS_fwrite(void *buffer, size_t size, size_t count, FILEHANDLE *file)
{
	UINT numBytesWritten = 0;
	if(fsMounted)
	{
		f_write((FIL*)&_currentFile, buffer, size * count, &numBytesWritten);
		return (size_t)numBytesWritten;
	}
	return 0;
}

void FATFS_fputc(CHAR character, FILEHANDLE *file)
{
	FATFS_fwrite(&character, 1, 1, file);
}

void FATFS_fputs(CHAR *str, FILEHANDLE *file)
{
	FATFS_fwrite(str, 1, strlen(str), file);
}
#endif


DIRECTORY* FATFS_dopen(CHAR *directory)
{
	char buffer[64];
	sprintf(&buffer[0], "1:/%s", directory);

	if(fsMounted)
	{
		memset(&_currentDirectory, 0, sizeof(_currentDirectory));

		if(f_opendir((DIR*)&_currentDirectory, buffer) == FR_OK)
			return &_currentDirectory;
	}
	return NULL;
}

FILEINFO* FATFS_dgetnextfile(DIRECTORY *directory)
{
	FRESULT res;
	if(fsMounted)
	{
		memset(&_currentFileInfo.lfname, 0, sizeof(_currentFileInfo.lfname));
		res = f_readdir((DIR*)directory, (FILINFO*)&_currentFileInfo);
		if(_currentFileInfo.fname[0] == 0) return NULL; // End of directory

		// We need to skip over directories and dot entries
		while(_currentFileInfo.fname[0] == '.' || (_currentFileInfo.fattrib & AM_DIR))
		{
			if(_currentFileInfo.fname[0] == 0) return NULL; // End of directory
			f_readdir((DIR*)directory, (FILINFO*)&_currentFileInfo);
		}

		return &_currentFileInfo;
	}
	return NULL;
}

CHAR* FATFS_GetFileName(FILEINFO *fileInfo)
{
	//if(*fileInfo->lfname != 0) return (CHAR*)fileInfo->lfname;
	return (CHAR*)fileInfo->fname;
}

BOOL FATFS_DirectoryExists(CHAR *directory)
{
	char buffer[64];
	sprintf(buffer, "1:%s", directory);
	if(FATFS_dopen(buffer) != NULL) return TRUE;
	return FALSE;
}
