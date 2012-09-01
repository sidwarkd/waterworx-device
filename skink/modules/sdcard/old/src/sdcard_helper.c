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
	FATFS_fread(str, 1, num, file);
	return str;
}

FILEHANDLE* FATFS_fopen(CHAR *filename, CHAR *mode)
{
	FRESULT res;
	BYTE flags;
	char fatfsFilename[32];
	sprintf(&fatfsFilename[0], "1:%s", filename);
	if(fsMounted == TRUE)
	{
		// Set the flags based on mode passed in
		if(strchr(mode, 'r') != NULL) flags |= FA_READ;
		if(strchr(mode, 'w') != NULL) flags |= FA_WRITE;
		if(strchr(mode, 'c') != NULL) flags |= FA_OPEN_ALWAYS;
		if(strchr(mode, 'n') != NULL) flags |= FA_CREATE_NEW;
		if(strchr(mode, 'o') != NULL) flags |= FA_CREATE_ALWAYS;


		res = f_open((FIL*)&_currentFile, &fatfsFilename[0], flags);
		if(res == FR_OK)
		{
			//f_lseek(&_currentFile, f_size(&_currentFile));
			return &_currentFile;
		}
	}

	return NULL;
}

void FATFS_fputc(CHAR character, FILEHANDLE *file)
{
	FATFS_fwrite(&character, 1, 1, file);
}

void FATFS_fputs(CHAR *str, FILEHANDLE *file)
{
	FATFS_fwrite(str, 1, strlen(str), file);
}

size_t FATFS_fread(void *buffer, size_t size, size_t count, FILEHANDLE *file)
{
	size_t numBytesRead = 0;
	if(fsMounted)
	{
		f_read((FIL*)file, buffer, size * count, numBytesRead);
		return numBytesRead;
	}
	return 0;
}

size_t FATFS_fwrite(void *buffer, size_t size, size_t count, FILEHANDLE *file)
{
	size_t numBytesWritten = 0;
	if(fsMounted)
	{
		f_write((FIL*)&_currentFile, buffer, size * count, &numBytesWritten);
		return numBytesWritten;
	}
	return 0;
}


DIRECTORY* FATFS_dopen(CHAR *directory)
{
	char buffer[64];
	sprintf(&buffer[0], "1:%s", dir);

	if(fsMounted)
	{
		if(f_opendir((DIR*)&_currentDirectory, &buffer[0]) == FR_OK)
			return &_currentDirectory;
	}
	return NULL;
}

FILEINFO* FATFS_dgetnextfile(DIRECTORY *directory)
{
	if(fsMounted)
	{
		f_readdir((DIR*)_currentDirectory, (FILINFO*)&_currentFileInfo));
	}
}

BOOL FATFS_DirectoryExists(CHAR *directory)
{
	if(FATFS_dopen(directory) != NULL) return TRUE;
	return FALSE;
}
