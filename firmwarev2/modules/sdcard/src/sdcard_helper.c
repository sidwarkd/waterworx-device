#include <sdcard/module.h>

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
		numOpenFiles--;
		free(file);
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
	FIL *newFile;
	char fatfsFilename[128];
	flags = 0;

	// Can't open any more files
	if(numOpenFiles == MAX_OPEN_FILES)
		return NULL;

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

		newFile = (FIL*)malloc(sizeof(FIL));
		if(newFile != NULL)
		{
			res = f_open(newFile, &fatfsFilename[0], flags);
			if(res == FR_OK)
			{
				f_lseek(newFile, 0);
				numOpenFiles++;
				return (FILEHANDLE*)newFile;
			}
			else
			{
				// Free the allocated memory
				free(newFile);
			}
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
		f_write((FIL*)file, buffer, size * count, &numBytesWritten);
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

BOOL FATFS_feof(FILEHANDLE *file)
{
	return (BOOL)f_eof((FIL*)file);
}


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
