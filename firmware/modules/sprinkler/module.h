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
	SS_WAITING = 0,
	SS_PROGRAM_START,
	SS_ZONE_START,
	SS_ZONE_RUNNING,
	SS_PROGRAM_END
}sprinklerState;

static SprinklerProgram sprinkler_programs[MAX_SPRINKLER_PROGRAMS];
static QueuedEvent program_queue[MAX_QUEUED_PROGRAMS];
QueuedEvent *CurrentEvent;
UINT8 eventsProcessed;

void SPRINKLER_Initialize(void);
void SPRINKLER_ProcessTasks(void);

#endif