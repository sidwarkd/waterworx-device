#include <sprinkler/module.h>

#ifdef DEBUGGING
#define START_PROGRAM_TEST	1
#endif

char program_json[] = "{ \
\"programs\":[	\
    {								\
        \"id\":\"111111\",			 \
        \"type\":1,				 \
        \"opt\":\"0,3.5\",			 \
        \"st\":\"1420\",			 \
        \"split\":1,				 \
        \"zones\":[				 \
            {\"id\":0,\"rt\":20},	 \
            {\"id\":1,\"rt\":10},	 \
            {\"id\":2,\"rt\":5},	 \
            {\"id\":3,\"rt\":5},	 \
            {\"id\":4,\"rt\":5}		 \
        ]						 \
    },							 \
    {							 \
        \"id\":\"222222\",			 \
        \"type\":1,				 \
        \"opt\":\"0,1,2,3.4,5,6\",	 \
        \"st\":\"0800\",			 \
        \"split\":1,				 \
        \"zones\":[				 \
            {\"id\":0,\"rt\":44},	 \
            {\"id\":1,\"rt\":33},	 \
			{\"id\":2,\"rt\":22},	 \
			{\"id\":3,\"rt\":11},	 \
            {\"id\":4,\"rt\":1}		 \
        ]							\
    }								\
]}";

static BOOL Initialized = FALSE;
static sprinklerState STATE_AFTER_CALLBACK;
static sprinklerState SPRINKLER_STATE = 99;

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

static void WriteProgramsToDisk()
{

	FILEHANDLE file;
	char buff[2048];

	ProgramsToJSON(&buff[0]);
	if(OpenFile("programs.jsn", &file, FA_WRITE | FA_OPEN_ALWAYS) == TRUE)
	{
		WriteFile(buff, &file);
		WriteFile("\r\n", &file);
		CloseFile(&file);
		SERIALUSB_Write("\r\nPrograms saved to card!");
	}
	else
	{
		SERIALUSB_Write("\r\nUnable to open file");
	}
}

static void SetModuleDateTime(HttpResponse *response)
{
	UINT16 year;
	UINT8 month;
	UINT8 day;
	UINT8 dayOfWeek;
	UINT8 hour;
	UINT8 minute;
	UINT8 second;
	#ifdef DEBUG_SPRINKLER_MODULE
	char timeString[32];
	#endif

	cJSON *root = cJSON_Parse(response->body);
	if(root)
	{
		year = (UINT16)cJSON_GetObjectItem(root,"y")->valueint;
		month = (UINT8)cJSON_GetObjectItem(root,"m")->valueint;
		day = (UINT8)cJSON_GetObjectItem(root,"d")->valueint;
		dayOfWeek = (UINT8)cJSON_GetObjectItem(root,"dow")->valueint;
		hour = (UINT8)cJSON_GetObjectItem(root,"h")->valueint;
		minute = (UINT8)cJSON_GetObjectItem(root,"min")->valueint;
		second = (UINT8)cJSON_GetObjectItem(root,"s")->valueint;

		SetDateTimeWithArgs(year, month, day, dayOfWeek, hour, minute, second);

		cJSON_Delete(root);

		#ifdef DEBUG_SPRINKLER_MODULE
		DateTimeToString(Now(), timeString);
		SERIALUSB_Write("\r\n");
		SERIALUSB_Write(timeString);
		#endif

		Initialized = TRUE;
		SPRINKLER_STATE = SS_CALLBACK_FINISHED;
	}
}

void SPRINKLER_ProcessTasks()
{
	UINT8 retVal;
	char retString[64];

	switch(SPRINKLER_STATE)
	{	
		case SS_GET_DATE_TIME:
			// Get a DateTime lock before going any further
			WIFI_PerformGet((CHAR*)"waterworx.herokuapp.com", (CHAR*)"/time", SetModuleDateTime);
			STATE_AFTER_CALLBACK = SS_LOAD_PROGRAMS;
			SPRINKLER_STATE = SS_WAITING_FOR_CALLBACK;
			break;

		case SS_CHECK_FOR_UPDATES:
			// Hit the server and see if there are any updates (firmware, programs, cancellations)
			
			STATE_AFTER_CALLBACK = SS_WAIT_FOR_PROGRAM;
			SPRINKLER_STATE = SS_WAITING_FOR_CALLBACK;
			break;

		case SS_LOAD_PROGRAMS:
			// Read stored program data.  If there is no data for programs then just continue
			// to poll for updates until there is.
			retVal = LoadProgramsFromJSON(&program_json[0]);
			if(retVal == 0)
			{
				// Successfully loaded programs
				SERIALUSB_Write("\r\nLoaded programs from JSON!");
				SPRINKLER_STATE = SS_CHECK_FOR_UPDATES;
			}
			else
			{
				// Failed to load programs
				sprintf(retString, "\r\nProgram load from JSON FAILED: %d", retVal);
				SERIALUSB_Write(retString);
				SPRINKLER_STATE = SS_ERROR;
			}
			break;



		case SS_WAIT_FOR_PROGRAM:
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

		case SS_WAITING_FOR_CALLBACK:
			// This state is only used while waiting for a callback to happen such as
			// for a TCP/IP operation.  Use STATE_AFTER_CALLBACK to set the next state
			asm ("nop");
			break;

		case SS_CALLBACK_FINISHED:
			SPRINKLER_STATE = STATE_AFTER_CALLBACK;
			break;

		case SS_ERROR:
			// The state machine broke.  Surface error somehow
			break;

		default:
			asm ("nop");
	}
}

void SPRINKLER_Initialize()
{
	UINT8 i;
	UINT8 j;
	for(i = 0; i < ARRAY_SIZE(sprinkler_programs); i++)
	{
		SprinklerProgram *program = sprinkler_programs + i;
		program->type = 0;
		for(j = 0; j < ARRAY_SIZE(program->zones); j++)
		{
			program->zones[j].id = -1;
		}
	}

	SPRINKLER_STATE = SS_GET_DATE_TIME;
}

UINT8 LoadProgramsFromJSON(char *json)
{
	//char output[1024];
	UINT8 returnVal = 0;
	UINT8 programIndex = 0;
	UINT8 zoneIndex = 0;
	char start_time[6]; 
	cJSON *program;
	cJSON *zone;
	cJSON *root = cJSON_Parse(json);
	if(root)
	{
		program = cJSON_GetObjectItem(root, "programs");
		
		if(program)
		{
			program = program->child;
			while(program)
			{
				SprinklerProgram *current_program = sprinkler_programs + programIndex;

				strcpy(current_program->id, cJSON_GetObjectItem(program,"id")->valuestring);
				current_program->type = (UINT8)cJSON_GetObjectItem(program,"type")->valueint;
				strcpy(current_program->type_options, cJSON_GetObjectItem(program,"opt")->valuestring);
				strcpy(start_time, cJSON_GetObjectItem(program,"st")->valuestring);
				MilitaryTimeStringToRTCCTime(start_time, &(current_program->start_time));
				current_program->split = (UINT8)cJSON_GetObjectItem(program,"split")->valueint;

				zone = cJSON_GetObjectItem(program,"zones");

				//sprintf(output, "\r\n\r\nProgram: %s\r\n  Type: %d\r\n  Options: %s\r\n  Start Time: %s\r\n  Split: %d\r\n  Zones:\r\n", id, type, opt, st, split);
				//SERIALUSB_Write(output);
				//SERIALUSB_ProcessTasks();

				if(zone)
				{
					zone = zone->child;
					while(zone)
					{
						SprinklerZone *current_zone = current_program->zones + zoneIndex;
						current_zone->id = (UINT8)cJSON_GetObjectItem(zone,"id")->valueint;
						current_zone->runtime = (UINT8)cJSON_GetObjectItem(zone,"rt")->valueint;
						//sprintf(output, "    ID: %d\r\n    Duration: %d\r\n", zid, duration);
						//SERIALUSB_Write(output);
						//SERIALUSB_ProcessTasks();
						zone = zone->next;
						zoneIndex++;
					}
				}
				else
				{
					returnVal = 3;
					break;
				}

				program = program->next;
				programIndex++;
			}
		}
		else
		{
			returnVal = 2;
		}

		cJSON_Delete(root);
	}
	else
	{
		returnVal = 1;
	}
	return returnVal;
}

UINT8 ProgramsToJSON(char *outputJSON)
{
	UINT8 returnVal = 0;
	SprinklerProgram *current_program;
	SprinklerZone *current_zone;
	char start_time[6]; 
	char *generatedJSON;

	cJSON *programArray;
	cJSON *program;
	cJSON *zoneArray;
	cJSON *zone;
	cJSON *root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "programs", programArray=cJSON_CreateArray());

	current_program = sprinkler_programs + 0;
	while(*(current_program->id))
	{
		program = cJSON_CreateObject();

		cJSON_AddStringToObject(program, "id", &(current_program->id[0]));
		cJSON_AddNumberToObject(program, "type", current_program->type);
		cJSON_AddStringToObject(program, "opt", &(current_program->type_options[0]));
		RTCCTimeToMilitaryTimeString(&(current_program->start_time), &start_time[0]);
		cJSON_AddStringToObject(program, "st", &start_time[0]);
		cJSON_AddNumberToObject(program, "split", current_program->split);

		cJSON_AddItemToObject(program, "zones", zoneArray=cJSON_CreateArray());

		current_zone = current_program->zones + 0;
		while(current_zone->id >= 0)
		{
			zone = cJSON_CreateObject();

			cJSON_AddNumberToObject(zone, "id", current_zone->id);
			cJSON_AddNumberToObject(zone, "rt", current_zone->runtime);

			cJSON_AddItemToArray(zoneArray, zone);
			current_zone += 1;
		}

		cJSON_AddItemToArray(programArray, program);
		current_program += 1;
	}

	generatedJSON = cJSON_PrintUnformatted(root);
	strcpy(outputJSON, generatedJSON);
	free(generatedJSON);
	cJSON_Delete(root);
}

