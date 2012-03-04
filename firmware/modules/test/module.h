#ifndef __TEST_MODULE
#define __TEST_MODULE

#include <userconfig.h>

#ifdef TESTING

#include <base/module.h>
#include <usb/module.h>

#ifndef NUM_MODULES_TO_TEST
#error Need to define NUM_MODULES_TO_TEST in userconfig.h
#endif

typedef BOOL (*TestFunction)(void);  // Function pointer for tests

typedef struct _test
{
	char name[16];
	BOOL passed;
	TestFunction run;
} Test;

typedef struct _testModule
{
	char Name[16];
	void (*Setup)(void);
	void (*Teardown)(void);
	void (*BeforeEach)(void);
	void (*AfterEach)(void);
	Test *Tests;
	UINT8 TestCount;
} TestModule;

TestModule *Modules[NUM_MODULES_TO_TEST];

void RunAllTests(void);
void RunTestsForNamedModule(char *moduleName);
void DisplayTestResults(void);

#endif  // End ifdef TESTING

#endif