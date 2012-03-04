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

// SetDateTime Tests
static BOOL Test1(void)
{
	return TRUE;
}

static BOOL Test2(void)
{
	return FALSE;
}

static BOOL Test3(void)
{
	return TRUE;
}

// SetDateTimeWithArgs Tests

// GetCurrentDateTimeAsDWORD Tests

// GetDateTimeAsDWORD Tests

// Now Tests

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

	RTCCTestModule.Tests = RTCC_Tests;
	RTCCTestModule.TestCount = ARRAY_SIZE(RTCC_Tests);
	return &RTCCTestModule;
}

#endif