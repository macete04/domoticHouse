#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include<stdbool.h>
#include<json-c/json.h>
#include<string.h>
#include"../customStructs/measurementsStruct.h"
#include"../customStructs/requestStruct.h"

#define HOUR "hour"
#define DAY "day"

typedef struct mqttClientInfos{

  char* broker;
  char* clientID;
  char* username;
  char* password;
  unsigned short int topicsArrayLength;
  char** topics;

}mqttClientInfos;

bool getInfosFromConfigFile(char* configFile, mqttClientInfos** mqttClientStuff);
bool isRequest(char* message);
bool getValuesFromMessage(char* mqttMessage, measurements** measurementsStruct);
bool getValuesForRequest(char* mqttMessage, requestStruct** requestDataStruct);

#endif
