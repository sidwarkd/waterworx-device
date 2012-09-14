#include <tcpip/wifi.h>
#include <json/module.h>

UINT8 WIFI_SCAN_ResultCount;

void WIFI_ScanResultsReady(UINT16 numResults)
{
  WIFI_SCAN_ResultCount = numResults;
}

CHAR* WIFI_ScanResultsToJSON(UINT8 numProfilesToRead)
{
  cJSON *root, *wifiProfile;
  UINT8 i = 0;
  static tWFScanResult profile;
  static CHAR *json;

  root = cJSON_CreateArray();

  for(i = 0; i < numProfilesToRead; i++)
  {
    WF_ScanGetResult(i, &profile);

    profile.ssid[profile.ssidLen] = '\0';
    cJSON_AddItemToArray(root, wifiProfile = cJSON_CreateObject());
    cJSON_AddStringToObject(wifiProfile, "ssid", profile.ssid);
    cJSON_AddNumberToObject(wifiProfile, "ID", i);
    cJSON_AddNumberToObject(wifiProfile, "apconfig", profile.apConfig);
    cJSON_AddNumberToObject(wifiProfile, "chan", profile.channel);
    cJSON_AddNumberToObject(wifiProfile, "ss", profile.rssi);

  }

  // root = cJSON_CreateObject();
  // cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
  // cJSON_AddItemToObject(root, "format", fmt=cJSON_CreateObject());
  // cJSON_AddStringToObject(fmt,"type",   "rect");
  // cJSON_AddNumberToObject(fmt,"width",    1920);
  // cJSON_AddNumberToObject(fmt,"height",   1080);
  // cJSON_AddFalseToObject (fmt,"interlace");
  // cJSON_AddNumberToObject(fmt,"frame rate", 24);

  json = (CHAR*)cJSON_PrintUnformatted(root);
  cJSON_Delete(root);
  //cJSON_Delete(fmt);

  return json;
}