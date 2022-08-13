#ifndef MQTTMESSAGEPARSER_H
#define MQTTMESSAGEPARSER_H

#include<stdio.h>
#include<assert.h>
#include"../customStructs/requestStruct.h"
#include"../customStructs/measurementsStruct.h"
#include"../jsonManager/jsonManager.h"
#include"../sqliteManager/manager.h"
#include"../globalVariables.h"

enum dbColumnsToSelect{
  SELECT_HOUR_COLUMN = 1,
  SELECT_DATE_COLUMN = 2
};

void* mqttMessageParser(void* mqttMessage);

#endif
