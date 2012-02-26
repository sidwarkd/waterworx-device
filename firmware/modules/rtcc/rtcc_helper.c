#include <rtcc/module.h>

void RTCC_Initialize()
{
	RtccOpen(0x10300000, 0x12021604, 0);
	while((RtccGetClkStat() != RTCC_CLK_ON));
}

void RTCC_Disable()
{
	RtccShutdown();
}

void SetDateTime(DateTime *dateTime)
{
	//RtccSetTimeDate(tm, dt);
}

void SetDateTimeWithArgs(UINT16 year, UINT8 month, UINT8 day, UINT8 dayOfWeek, UINT8 hour, UINT8 minute, UINT8 second)
{
	
}


DWORD GetCurrentDateTimeAsDWORD()
{
	DateTime *now;
	now = Now();
	return GetDateTimeAsDWORD(now);
}

DWORD GetDateTimeAsDWORD(DateTime *dateTime)
{
	return (((DWORD)dateTime->year - 1980) << 25)
			| ((DWORD)dateTime->month << 21)
			| ((DWORD)dateTime->day << 16)
			| (WORD)(dateTime->hour << 11)
			| (WORD)(dateTime->minute << 5)
			| (WORD)(dateTime->second >> 1);
}

DateTime* Now(void)
{
	rtccTime tm;
	rtccDate dt;

	// Get the current time in BCD
	RtccGetTimeDate(&tm, &dt);	

	// Translate the time to a DateTime struct
	_now.year = 2000;
	_now.year += ((dt.year & TENS_MASK)>>4)*10;
	_now.year += (dt.year & ONES_MASK);
	_now.month = 0 + ((dt.mon & TENS_MASK)>>4)*10;
	_now.month += (dt.mon & ONES_MASK);
	_now.day = 0 + ((dt.mday & TENS_MASK)>>4)*10;
	_now.day += (dt.mday & ONES_MASK);
	_now.day_of_week = 0 + (dt.wday & ONES_MASK);
	_now.hour = 0 + ((tm.hour & TENS_MASK)>>4)*10;
	_now.hour += (tm.hour & ONES_MASK);
	_now.minute = 0 + ((tm.min & TENS_MASK)>>4)*10;
	_now.minute += (tm.min & ONES_MASK);
	_now.second = 0 + ((tm.sec & TENS_MASK)>>4)*10;
	_now.second += (tm.sec & ONES_MASK);

	return &_now;
}

void DateTimeToString(DateTime *dateTime, char *outputString)
{
	sprintf(outputString, "%d %s %d, %02d:%02d:%02d", dateTime->day, MONTHS[dateTime->month - 1], dateTime->year, dateTime->hour, dateTime->minute, dateTime->second);
}

