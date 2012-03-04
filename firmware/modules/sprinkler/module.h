#ifndef __SPRINKLER_MODULE_H
#define __SPRINKLER_MODULE_H

#include <userconfig.h>
#include <plib.h>

#define RELAY_OFF	0
#define RELAY_ON	1

typedef struct
{
	UINT8 	id;
	WORD	runtime;
}SprinklerZone;

typedef struct
{
	UINT8 id;
	SprinklerZone zones[MAX_ZONES_PER_PROGRAM];
}SprinklerProgram;

typedef struct
{
	rtccDate start_date;
	rtccTime start_time;
	SprinklerProgram *program;
	SprinklerZone *currentZone;
}QueuedEvent;

typedef enum
{  
	SS_STARTUP = 0,			// Unit just turned on
	SS_CONFIGURED,			// All setting have been applied.  Ready for operation
	SS_UPDATING,				// The state for phoning home and getting updates
	SS_WAITING,					// Waiting for the next program to start.  Idle state
	SS_PROGRAM_START,		// State to prepare everything for a program run
	SS_ZONE_START,			// Start of each zone in a program
	SS_ZONE_RUNNING,		// Zone is running.
	SS_PROGRAM_END			// Post program cleanup before returning to SS_WAITING
}sprinklerState;

static SprinklerProgram sprinkler_programs[MAX_SPRINKLER_PROGRAMS];
static QueuedEvent program_queue[MAX_QUEUED_PROGRAMS];
QueuedEvent *CurrentEvent;
UINT8 eventsProcessed;

void SPRINKLER_Initialize(void);
void SPRINKLER_ProcessTasks(void);

#endif