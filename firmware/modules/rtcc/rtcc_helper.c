#include <rtcc/module.h>

void RTCC_Initialize()
{
	rtccDate dt, dAlrm;
	rtccTime tm, tAlrm;

	
	RtccInit();
	while((RtccGetClkStat() != RTCC_CLK_ON));
	RtccOpen(0x10300000, 0x00042906, 0);

	_nextAlarm.hasFired = TRUE;
}

void RTCC_Disable()
{
	RtccShutdown();
}

void RTCC_ProcessTasks()
{
	// Check for alarm condition
	if(!_nextAlarm.hasFired && (GetCurrentDateTimeAsDWORD() > GetDateTimeAsDWORD(&(_nextAlarm.time))))
	{
		_nextAlarm.callback();
		_nextAlarm.hasFired = TRUE;
	}
}

void RTCC_SetNextAlarm(DateTime *dateTime, void (*callback)(void))
{
	// Copy alarm values
	_nextAlarm.time.year = dateTime->year;
	_nextAlarm.time.month = dateTime->month;
	_nextAlarm.time.day = dateTime->day;
	_nextAlarm.time.day_of_week = dateTime->day_of_week;
	_nextAlarm.time.hour = dateTime->hour;
	_nextAlarm.time.minute = dateTime->minute;
	_nextAlarm.time.second = dateTime->second;

	_nextAlarm.callback = callback;
	_nextAlarm.hasFired = FALSE;
}

void SetDateTime(DateTime *dateTime)
{
	rtccTime tm;
	rtccDate dt;
	UINT16 year;

	year = dateTime->year - 2000;

	dt.year = (year / 10)<<4;
	dt.year += (year % 10);
	dt.mon = (dateTime->month / 10)<<4;
	dt.mon += (dateTime->month % 10);
	dt.mday = (dateTime->day / 10)<<4;;
	dt.mday += (dateTime->day % 10);;
	dt.wday = dateTime->day_of_week;
	tm.hour = (dateTime->hour / 10)<<4;
	tm.hour += (dateTime->hour % 10);
	tm.min = (dateTime->minute / 10)<<4;
	tm.min += (dateTime->minute % 10);
	tm.sec = (dateTime->second / 10)<<4;
	tm.sec += (dateTime->second % 10);

	RtccSetTimeDate(tm.l, dt.l);
}

void SetDateTimeWithArgs(UINT16 year, UINT8 month, UINT8 day, UINT8 dayOfWeek, UINT8 hour, UINT8 minute, UINT8 second)
{
	DateTime dateTime;
	dateTime.year = year;
	dateTime.month = month;
	dateTime.day = day;
	dateTime.day_of_week = dayOfWeek;
	dateTime.hour = hour;
	dateTime.minute = minute;
	dateTime.second = second;

	SetDateTime(&dateTime);
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

void MilitaryTimeStringToRTCCTime(char *militaryTimeString, rtccTime *time)
{	
	// Format will be HHMM
	INT timeVal;

	if(strlen(militaryTimeString) == 4)
	{
		timeVal = atoi(militaryTimeString);

		time->hour = (timeVal / 1000)<<4;
		time->hour += (timeVal / 100);
		time->min = (timeVal / 10)<<4;
		time->min += (timeVal % 10);
		time->sec = 0;
	}
	else
		time = NULL;
}

void RTCCTimeToMilitaryTimeString(rtccTime *time, char *militaryTimeString)
{
	int hour;
	int minute;

	hour = 0 + ((time->hour & TENS_MASK)>>4)*10;
	hour += (time->hour & ONES_MASK);
	minute = 0 + ((time->min & TENS_MASK)>>4)*10;
	minute += (time->min & ONES_MASK);

	sprintf(militaryTimeString, "%02.2d%02.2d", hour, minute);
}

