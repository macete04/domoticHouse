#ifndef MQTTMESSAGEPARSER_H
#define MQTTMESSAGEPARSER_H

#include<stdio.h>
#include<assert.h>
#include"../customStructs/requestStruct.h"
#include"../customStructs/measurementsStruct.h"
#include"../jsonManager/jsonManager.h"
#include"../sqliteManager/manager.h"
#include"../globalVariables.h"

void* mqttMessageParser(void* mqttMessage);

#endif
