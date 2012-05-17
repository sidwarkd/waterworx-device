#ifndef TCPIP_MODULE_H
#define TCPIP_MODULE_H

#include <userconfig.h>
#include <base/module.h>
#include <TCPIPConfig.h>
#include <TCPIP Stack/TCPIP.h>

#include <WF_Config.h>

#include <TCPIP Stack/WFEasyConfig.h>

// Put compile errors if missing WF pin definitions

// Members
/*#define MAX_HEADERS					5
#define MAX_HEADER_NAME_LENGTH		16
#define MAX_HEADER_VALUE_LENGTH		64
#define MAX_URL_LENGTH				128
#define MAX_METHOD_LENGTH			5
#define MAX_HTTP_VERSION_LENGTH		5
#define MAX_REQUEST_BODY_LENGTH		256
#define MAX_RESPONSE_BODY_LENGTH	1024
#define HTTP_STATUS_LINE_OVERHEAD	10
#define MAX_STATUS_LINE_LENGTH		(MAX_METHOD_LENGTH + MAX_URL_LENGTH + MAX_HTTP_VERSION_LENGTH + HTTP_STATUS_LINE_OVERHEAD)
#define PACKET_NEWLINE				"\r\n"
#define MAX_RESPONSE_SIZE			2048

typedef struct _HeaderItem
{
	BYTE name[MAX_HEADER_NAME_LENGTH];
	BYTE value[MAX_HEADER_VALUE_LENGTH];
} HeaderItem;

typedef struct _HttpResponse
{
	HeaderItem headers[MAX_HEADERS];
	WORD status_code;
	BYTE body[2048];
} HttpResponse;

typedef struct _HttpRequest
{
	WORD port;
	BYTE method[MAX_METHOD_LENGTH];
	BYTE url[MAX_URL_LENGTH];
	BYTE http_version[MAX_HTTP_VERSION_LENGTH];
	HeaderItem headers[MAX_HEADERS];
	BYTE *body;
} HttpRequest;

struct pending_packet
{
	HttpRequest request;
	void (*callback)(HttpResponse *response);
}WiFiPacket;

struct pending_packet *CurrentPacket;
*/

// HardwareProfile.h
#define GENERATED_BY_TCPIPCONFIG "Version 1.0.4168.28618"

// main.h
#define SaveAppConfig(a)
//void ProcessTCPRequests(void);
void DisplayIPValue(IP_ADDR IPVal);

// Core Module Functions
void TCPIP_Initialize(void);
void TCPIP_PerformStackTasks(void);
//void WIFI_PerformGet(CHAR *server, CHAR* url, void (*callback)(HttpResponse *response));
//void WIFI_PerformPost(CHAR *server, CHAR* url, CHAR* body, void (*callback)(HttpResponse *response));

// Helper Functions
//BYTE* GetHeaderValue(CHAR *key, HeaderItem *headers);
//static void GenerateRequestPacket(HttpRequest *request, BYTE *packet);
//static void ParseHttpResponsePacket(BYTE *buffer, HttpResponse *response);

#endif