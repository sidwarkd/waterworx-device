#ifndef __RTCC_MODULE
#define __RTCC_MODULE

#include <plib.h>
#include <userconfig.h>

// RTCC Time is in the format of 0xhhmmss00 where trailing 00 are just unused bits
// RTCC Date is in the format of 0xyymmddww where ww is the integer of the weekday 0=Sunday

typedef struct _DateTime
{
	UINT16 year;
	UINT8 month;
	UINT8 day;
	UINT8 day_of_week;
	UINT8 hour;
	UINT8 minute;
	UINT8 second;
}DateTime;

typedef struct _Alarm
{
    DateTime time;
    void (*callback)(void);
    BOOL hasFired;
}Alarm;

static DateTime _now;
static char *MONTHS[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
static Alarm _nextAlarm;

// BCD conversion masks
#define TENS_MASK 0xF0
#define ONES_MASK	0x0F


void RTCC_Initialize(void);
void RTCC_Disable(void);
void RTCC_ProcessTasks(void);
DWORD GetDateTimeAsDWORD(DateTime *dateTime);
DWORD GetCurrentDateTimeAsDWORD(void);
void SetDateTime(DateTime *dateTime);
void SetDateTimeWithArgs(UINT16 year, UINT8 month, UINT8 day, UINT8 dayOfWeek, UINT8 hour, UINT8 minute, UINT8 second);
DateTime* Now(void);
void DateTimeToString(DateTime *dateTime, char *outputString);
void MilitaryTimeStringToRTCCTime(char *militaryTimeString, rtccTime *time);
void RTCCTimeToMilitaryTimeString(rtccTime *time, char *militaryTimeString);

// Alarm Functions
void RTCC_SetNextAlarm(DateTime *dateTime, void (*callback)(void));

#ifdef TESTING
#include <test/module.h>
#define RTCC_TestCount	5
TestModule *RTCC_GetTestModule(void);
Test RTCC_Tests[RTCC_TestCount];
TestModule RTCCTestModule;
#endif


#endif