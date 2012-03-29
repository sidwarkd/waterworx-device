#ifndef __SPRINKLER_MODULE_H
#define __SPRINKLER_MODULE_H

#include <userconfig.h>
#include <plib.h>
#include <rtcc/module.h>
#include <usb/module.h>
#include <wifi/module.h>
#include <json/module.h>

#define RELAY_OFF	0
#define RELAY_ON	1

typedef struct
{
	UINT8 	id;
	UINT8	runtime;
}SprinklerZone;

typedef struct
{
	char id[32];
	UINT8 type;
	char type_options[64];
	rtccTime start_time;
	SprinklerZone zones[MAX_ZONES_PER_PROGRAM];
	UINT8 split;
}SprinklerProgram;

typedef enum
{  
	SS_GET_DATE_TIME = 0,	// Unit just turned on
	SS_LOAD_PROGRAMS,		// All settings have been applied.  Ready for operation
	SS_CHECK_FOR_UPDATES,	// The state for phoning home and getting updates
	SS_WAIT_FOR_PROGRAM,	// Waiting for the next program to start.  Idle state
	SS_PROGRAM_START,		// State to prepare everything for a program run
	SS_ZONE_START,			// Start of each zone in a program
	SS_ZONE_RUNNING,		// Zone is running.
	SS_PROGRAM_END,			// Post program cleanup before returning to SS_WAITING
	SS_WAITING_FOR_CALLBACK,// Wait for a background operation to finish
	SS_CALLBACK_FINISHED,	// Fired when callback is done
	SS_ERROR
}sprinklerState;

static SprinklerProgram sprinkler_programs[MAX_SPRINKLER_PROGRAMS];


void SPRINKLER_Initialize(void);
void SPRINKLER_ProcessTasks(void);

UINT8 LoadProgramsFromJSON(char *json);
UINT8 ProgramsToJSON(char *outputJSON);

#endif