#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

#include <userconfig.h>
#include <base/module.h>
#include <TCPIP Stack/TCPIP.h>

#include <wifi/TCPIPConfig.h>
#include <wifi/WF_Config.h>

// Put compile errors if missing WF pin definitions

// HardwareProfile.h
#define GENERATED_BY_TCPIPCONFIG "Version 1.0.4168.28618"
#define PIC32_GP_SK_DM320001


// main.h
#define SaveAppConfig(a)
void GenericTCPClient(void);

// Core Module Functions
void WIFI_Initialize(void);
void WIFI_PerformStackTasks(void);

#endif