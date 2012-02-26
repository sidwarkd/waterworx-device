#include <sdcard/module.h>


BOOL OpenFile(char *filename, FILEHANDLE *stream, BYTE flags)
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
			SERIALUSB_Write(&fatfsFilename[0]);
		}
	}
	else
	{
		SERIALUSB_Write("FS not mounted");
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