#ifndef _WIFI_MODULE
#define _WIFI_MODULE

#include <base/module.h>
#include <TCPIP Stack/TCPIP.h>
#include <TCPIP Stack/WFApi.h>


// Definition to represent an IP address
#define IP_ADDR   DWORD_VAL

typedef struct
{
  IP_ADDR   MyIPAddr;               // IP address
  IP_ADDR   MyMask;                 // Subnet mask
  IP_ADDR   MyGateway;              // Default Gateway
  IP_ADDR   PrimaryDNSServer;       // Primary DNS Server
  IP_ADDR   SecondaryDNSServer;     // Secondary DNS Server
  IP_ADDR   DefaultIPAddr;          // Default IP address
  IP_ADDR   DefaultMask;            // Default subnet mask
  BYTE      NetBIOSName[16];        // NetBIOS name
  MAC_ADDR  MyMACAddr;              // Application MAC address

  BYTE      MySSID[32];             // Wireless SSID (if using MRF24WB0M)
  BYTE      SsidLength;             // number of bytes in SSID
  BYTE      SecurityMode;           // WF_SECURITY_OPEN or one of the other security modes
  BYTE      SecurityKey[64];        // WiFi Security key, or passphrase.   
  BYTE      SecurityKeyLength;      // number of bytes in security key (can be 0)
  BYTE      WepKeyIndex;            // WEP key index (only valid for WEP)
  BYTE      networkType;

} NETWORK_CONFIG;

CHAR* WIFI_ScanResultsToJSON(UINT8 numProfilesToRead);
void WIFI_ScanResultsReady(UINT16 numResults);

extern NETWORK_CONFIG NetworkConfiguration;
extern UINT8 WIFI_SCAN_ResultCount;

#endif