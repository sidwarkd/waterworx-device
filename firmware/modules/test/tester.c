#include <test/module.h>
#ifdef TESTING
static void RunAllTestsInModule(TestModule *module)
{
	UINT8 i;
	BOOL testResult;

	module->Setup();
	for(i = 0; i < module->TestCount; i++)
	{
		Test *currentTest = module->Tests + i;
		module->BeforeEach();
		testResult = currentTest->run();
		currentTest->passed = testResult;
		module->AfterEach();
	}
	module->Teardown();
}

void RunAllTests()
{
	UINT8 i;

	for(i = 0; i < ARRAY_SIZE(Modules); i++)
	{
		TestModule *module = Modules[i];
		RunAllTestsInModule(module);
	}
}

void RunTestsForNamedModule(char *moduleName)
{
	UINT8 i;

	for(i = 0; i < ARRAY_SIZE(Modules); i++)
	{
		TestModule *module = Modules[i];
		if(strcmp(moduleName, module->Name) == 0)
		{
			RunAllTestsInModule(module);
			break;
		}
	}
}

// DisplayTestResult can be modified to show test results in different ways such as:
// - LED flashes
// - Write to output
// - USB communication
// - Attached screen
void DisplayTestResults(void)
{
	UINT8 moduleIndex;
	UINT8 testIndex;
	char buffer[64];

	for(moduleIndex = 0; moduleIndex < ARRAY_SIZE(Modules); moduleIndex++)
	{
		TestModule *module = Modules[moduleIndex];
		sprintf(buffer, "\r\n\r\nTest Results For %s Module", module->Name);
		SERIALUSB_Write(buffer);
		SERIALUSB_ProcessTasks();

		for(testIndex = 0; testIndex < module->TestCount; testIndex++)
		{
			Test *test = module->Tests + testIndex;
			sprintf(buffer, "\r\n%s: %s", test->name, (test->passed)?"PASS":"FAIL");
			SERIALUSB_Write(buffer);
			SERIALUSB_ProcessTasks();
		}
	}
}
#endif