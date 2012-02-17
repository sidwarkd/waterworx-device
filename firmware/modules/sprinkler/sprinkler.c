#include <sprinkler/module.h>

#ifdef DEBUGGING
#define START_PROGRAM_TEST	1
#endif

static void TurnOffAllZones()
{
	LATE = RELAY_OFF;
}

static void TurnOnZone(UINT8 zoneID)
{
	TurnOffAllZones();
	if(zoneID <= 3)
		LATE |= (1 << zoneID);
}

void SPRINKLER_ProcessTasks()
{
	static sprinklerState SPRINKLER_STATE = SS_WAITING;

	switch(SPRINKLER_STATE)
	{
		case SS_WAITING:
			// If the next queued program time interrup has fired start that program.
			// Otherwise just wait here.
			if(SPRINKLER_TIME_IF || START_PROGRAM_TEST)
			{
				SPRINKLER_TIME_IF = 0;
				SPRINKLER_STATE++;
			}
			break;

		case SS_PROGRAM_START:
			// Load the first station
			break;

		case SS_ZONE_START:
			break;

		case SS_ZONE_RUNNING:
			break;

		case SS_PROGRAM_END:
			break;
	}
}

void SPRINKLER_Initialize()
{
	// Read the programs and queue data from non-volatile data store

	// Load the next program
	programsProcessed = 0;
	CurrentProgram = program_queue[programsProcessed];

	// Set the interrupt time for the program
}

