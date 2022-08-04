#include<stdio.h>
#include<stdlib.h>
#include"sqliteManager/manager.h"
#include"globalVariables.h"

#define NUMBER_OF_COLUMNS 6

int main(){

  databaseManager dbManager = DATABASE_MANAGER_INITIALIZER;
  databaseManager* ptr_dbManager = &dbManager;

  bool isSuccess;
  
  printf("Creating database...\n");
  isSuccess = createDatabase(&ptr_dbManager);
  switch (isSuccess){

    case true:
      printf("SUCCESS: database created\n");
      break;

    case false:
      printf("FAILED: database was NOT created\n");
      exit(EXIT_FAILURE);
  } 
  
  char* columnsAndTypes[NUMBER_OF_COLUMNS] = {
    "DAYOFMEASUREMENT date",
    "DEVICEID TEXT",
    "HOUROFMEASUREMENT INTEGER", 
    "TEMPERATURE REAL", 
    "HUMIDITY REAL", 
    "CO2PPM INTEGER"
  };

  printf("INFO: Creating table with the following columns:\n");
  for(short int i = 0; i < NUMBER_OF_COLUMNS; ++i){
    printf("%s, ", columnsAndTypes[i]);
  }
  printf(", do you want to proceed? y/N: ");
  char confirmOrDeny = getchar();

  switch (confirmOrDeny){
    case 'y':
      printf("Ok, proceeding...\n");
      break;
    case 'N':
      printf("Ok, exiting...\n");
      return 0;

  }
  
  isSuccess = createTable(MEASUREMENTS_TABLE, columnsAndTypes, NUMBER_OF_COLUMNS, &ptr_dbManager);
  switch (isSuccess){
    case true:
      printf("SUCCESS: Table created successfully\n");
      break;
    
    case false:
      printf("FAILED: table was NOT created\n");
      exit(EXIT_FAILURE);
  }

  // TODO: implement checking for folder and database file before printing this out
  printf("SUCCESS: your system was successfully prepared!\n");
  return 0;
}
