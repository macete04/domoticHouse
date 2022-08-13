#include<stdio.h>
#include<stdlib.h>
#include"sqliteManager/manager.h"
#include"globalVariables.h"

#define NUMBER_OF_COLUMNS 6
#define pass printf("this function still has to be developed")


void printHelp();

int main(int argc, char* argv[]){
  
  if(argc == 2){
    if(strcmp("help", argv[1]) == 0){
      printHelp();      
    }
  }

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
  
  // now we create config.json file
  char* homeDir = getenv("HOME");
  char* wantedDirAndFileName = "/domoticHouseUtilities/config.json";

  char* configFileDir = malloc(strlen(homeDir)+strlen(wantedDirAndFileName));
  
  memset(configFileDir, 0, strlen(homeDir)+strlen(wantedDirAndFileName));

  strcat(configFileDir, homeDir);
  strcat(configFileDir, wantedDirAndFileName);
  
  printf("Creating config.json file in %s\n", configFileDir);
  FILE* configFile;
  
  configFile = fopen(configFileDir, "w+");
  if(configFile == NULL){
    printf("FAILED: config.json file was not created");
    exit(EXIT_FAILURE);  
  }

  // we now write to the file all the fields we need
  char* configJsonFileBase = 
    "{\n\t\"broker\": ,\n\t\"client_id\": ,\n\t\"username\": ,\n\t\"password\": ,\n\t\"topics\": []\n}";
  fprintf(configFile, "%s", configJsonFileBase);
  
  free(configFileDir);
  fclose(configFile);
  
  // TODO: implement checking for folder and database file before printing this out
  printf("SUCCESS: your system was successfully prepared!\n");
  return 0;
}

void printHelp(){

  pass;

}
