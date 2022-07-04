#ifndef MANAGER_H
#define MANAGER_H

#include<sqlite3.h>
#include<stdbool.h>
#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>

#include"../sensorTypes/sensorTypes.h"

typedef struct databaseManager{
  
  char* name;
  char* parentDirectory;
  char* folder;
  
}databaseManager;

enum DBState{
  DB_FAIL = false,
  DB_SUCCESS = true,
};

bool createDatabase(databaseManager** dbManager);
bool createTable(char* tableName, char** colAndTypes, short int sizeOfArray, databaseManager** dbManager);
bool insertAndSaveMeasurements(char* tableToSaveTo, measurements** measurementsToSave, databaseManager** dbManager);


#endif
