#ifndef MANAGER_H
#define MANAGER_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stddef.h>
#include<sqlite3.h>
#include<sys/stat.h>
#include<string.h>

#include"../customStructs/measurementsStruct.h"

#define DATABASE_MANAGER_INITIALIZER {"/measurements.db", getenv("HOME"), "/domoticHouseUtilities"}

typedef struct databaseManager{

  char* name;
  char* parentDirectory;
  char* folder;

}databaseManager;

typedef struct fetchedData{

  unsigned short int indexNumber;
  double* fetchedDataArray;

}fetchedData;

enum DBState{
  DB_FAIL = false,
  DB_SUCCESS = true,
};

bool createDatabase(databaseManager** dbManager);
bool createTable(
    const char* tableName, 
    char** colAndTypes, 
    short int sizeOfArray, 
    databaseManager** dbManager);

bool insertAndSaveMeasurements(
    const char* tableToSaveTo, 
    measurements** measurementsToSave, 
    databaseManager** dbManager);

bool getTempHumidityOrCo2Data(
    databaseManager** dbManager, 
    fetchedData** fetchedDataFromDb, 
    const unsigned short int columnToSelect,
    const unsigned short int parameterFromJson,
    const char* tableName, 
    const char* minHour, 
    const char* maxHour);

#endif
