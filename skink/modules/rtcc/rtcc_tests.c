#include <rtcc/module.h>

#ifdef TESTING

// Setup
static void RTCC_TestSetup()
{
	RTCC_Initialize();
}

// Teardown
static void RTCC_TestTeardown()
{
	RTCC_Disable();
}

static void RTCC_BeforeEachTest()
{
	return;
}

static void RTCC_AfterEachTest()
{
	return;
}

// Verify SetDateTime handles single digit months,days,hours,minutes,and seconds
static BOOL Test1(void)
{
	DateTime *dt;
	// Set the time to Jan 1, 2010 01:01:01
	SetDateTimeWithArgs(2010, 1, 1, 0, 1, 1, 1);

	// Get the time.  It should happen fast enough that it should return the same
	dt = Now();

	// Verify results
	if(dt->year == 2010 && dt->month == 1 && dt->day == 1 && dt->hour == 1 && dt->minute == 1 && dt->second == 1)
	{
		return TRUE;
	}
	return FALSE;
}

// Verify SetDateTime handles double digit months,months,days,hours,minutes,and seconds
static BOOL Test2(void)
{
	DateTime *dt;
	// Set the time to Jan 1, 2010 01:01:01
	SetDateTimeWithArgs(2010, 10, 20, 0, 18, 18, 18);

	// Get the time.  It should happen fast enough that it should return the same
	dt = Now();

	// Verify results
	if(dt->year == 2010 && dt->month == 10 && dt->day == 20 && dt->hour == 18 && dt->minute == 18 && dt->second == 18)
	{
		return TRUE;
	}
	return FALSE;
}

// GetDateTimeAsDWORD can be used for time comparisons
static BOOL Test3(void)
{
	DateTime dt1;
	DateTime dt2;

	dt1.year = 2010;
	dt1.month = 1;
	dt1.day = 1;
	dt1.hour = 1;
	dt1.minute = 1;
	dt1.second = 1;

	dt2.year = 2010;
	dt2.month = 1;
	dt2.day = 1;
	dt2.hour = 1;
	dt2.minute = 1;
	dt2.second = 1;

	if(GetDateTimeAsDWORD(&dt1) != GetDateTimeAsDWORD(&dt2))
		return FALSE;

	dt2.second += 1;

	if(GetDateTimeAsDWORD(&dt2) < GetDateTimeAsDWORD(&dt1))
		return FALSE;

	dt1.minute += 1;

	if(GetDateTimeAsDWORD(&dt1) < GetDateTimeAsDWORD(&dt2))
		return FALSE;

	dt2.hour += 1;

	if(GetDateTimeAsDWORD(&dt2) < GetDateTimeAsDWORD(&dt1))
		return FALSE;

	dt1.day += 1;

	if(GetDateTimeAsDWORD(&dt1) < GetDateTimeAsDWORD(&dt2))
		return FALSE;

	dt2.month += 1;

	if(GetDateTimeAsDWORD(&dt2) < GetDateTimeAsDWORD(&dt1))
		return FALSE;

	dt1.year += 1;

	if(GetDateTimeAsDWORD(&dt1) < GetDateTimeAsDWORD(&dt2))
		return FALSE;

	return TRUE;
}

// MilitaryTimeStringToRTCCTime
static BOOL Test4(void)
{
	char timeString[12];
	rtccTime tm;
	rtccExpectedTime etm;

	// Time string can have 0 in 4th position
	strcpy(timeString, "0111");
	etm = 0x01110000;
	MilitaryTimeStringToRTCCTime(&timeString[0], &tm);
	if(etm != tm) return FALSE;

	// Time string can have 0 in 3rd position
	strcpy(timeString, "1011");
	etm = 0x10110000;
	MilitaryTimeStringToRTCCTime(&timeString[0], &tm);
	if(etm != tm) return FALSE;

	// Time string can have 0 in 2nd position
	strcpy(timeString, "2105");
	etm = 0x21050000;
	MilitaryTimeStringToRTCCTime(&timeString[0], &tm);
	if(etm != tm) return FALSE;

	// Time string can have 0 in 1st position
	strcpy(timeString, "1130");
	etm = 0x11300000;
	MilitaryTimeStringToRTCCTime(&timeString[0], &tm);
	if(etm != tm) return FALSE;

	// Function returns null if invalid short string passed
	strcpy(timeString, "123");;
	MilitaryTimeStringToRTCCTime(&timeString[0], &tm);
	if(tm != NULL) return FALSE;

	// Function returns null if invalid long string passed
	strcpy(timeString, "123456");
	MilitaryTimeStringToRTCCTime(&timeString[0], &tm);
	if(tm != NULL) return FALSE;
}

// RTCCTimeToMilitaryTimeString
static BOOL Test5(void)
{
	char timeString[12];
	char expected[12];
	rtccTime tm;

	// Time string can have 0 in 4th position
	strcpy(expected, "0111");
	tm = 0x01110000;
	RTCCTimeToMilitaryTimeString( &tm, &timeString[0]);
	if(strcmp(expect, timeString) != 0) return FALSE;

	// Time string can have 0 in 3rd position
	strcpy(expected, "1011");
	tm = 0x10110000;
	RTCCTimeToMilitaryTimeString( &tm, &timeString[0]);
	if(strcmp(expect, timeString) != 0) return FALSE;

	// Time string can have 0 in 2nd position
	strcpy(expected, "2105");
	tm = 0x21050000;
	RTCCTimeToMilitaryTimeString( &tm, &timeString[0]);
	if(strcmp(expect, timeString) != 0) return FALSE;

	// Time string can have 0 in 1st position
	strcpy(expected, "1130");
	tm = 0x11300000;
	RTCCTimeToMilitaryTimeString( &tm, &timeString[0]);
	if(strcmp(expect, timeString) != 0) return FALSE;
}


TestModule *RTCC_GetTestModule()
{
	Test *test;

	strcpy(RTCCTestModule.Name, "RTCC");
	RTCCTestModule.Setup = RTCC_TestSetup;
	RTCCTestModule.Teardown = RTCC_TestTeardown;
	RTCCTestModule.BeforeEach = RTCC_BeforeEachTest;
	RTCCTestModule.AfterEach = RTCC_AfterEachTest;

	// Configure the test array
	test = RTCC_Tests + 0;
	strcpy(test->name, "Test1");
	test->run = Test1;

	test = RTCC_Tests + 1;
	strcpy(test->name, "Test2");
	test->run = Test2;

	test = RTCC_Tests + 2;
	strcpy(test->name, "Test3");
	test->run = Test3;

	test = RTCC_Tests + 3;
	strcpy(test->name, "Test4");
	test->run = Test4;

	test = RTCC_Tests + 4;
	strcpy(test->name, "Test5");
	test->run = Test5;

	/*test = RTCC_Tests + 2;
	strcpy(test->name, "Test6");
	test->run = Test6;

	test = RTCC_Tests + 0;
	strcpy(test->name, "Test7");
	test->run = Test7;

	test = RTCC_Tests + 1;
	strcpy(test->name, "Test8");
	test->run = Test8;

	test = RTCC_Tests + 2;
	strcpy(test->name, "Test9");
	test->run = Test9;

	test = RTCC_Tests + 2;
	strcpy(test->name, "Test10");
	test->run = Test10;*/

	RTCCTestModule.Tests = RTCC_Tests;
	RTCCTestModule.TestCount = RTCC_TestCount;
	return &RTCCTestModule;
}

#endif