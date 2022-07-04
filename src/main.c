#include<stdio.h>
#include<stdlib.h>
#include"sqliteManager/manager.h"
#include"sensorTypes/sensorTypes.h"
#include"dateManager/dateManager.h"

#define NUMBER_OF_COLUMNS 4


int main(){
  
  // creating db struct
  databaseManager dbManager = {"/measurements.db", getenv("HOME"), "/NetAtmoOpenSourceUtilities"};
  databaseManager *ptr_dbManager = &dbManager;
  
  measurements m = {getDate(), 23.2, 37.7, 123};
  measurements *ptr_m = &m;
  
  char* MEASUREMENTS_TABLE_NAME = " measurementsTable ";

  bool exit;

  exit = createDatabase(&ptr_dbManager);
  
  printf("%s", exit ? "Database created successfully\n" : "Something went wrong while creating the DB\n");
  
  // creating table
  char* columnsAndTypes[NUMBER_OF_COLUMNS] = {"DAYOFMEASUREMENT date", "TEMPERATURE REAL", "HUMIDITY REAL", "CO2PPM INTEGER"};
  
  printf("calling createTable()\n");
  exit = createTable(MEASUREMENTS_TABLE_NAME, columnsAndTypes, NUMBER_OF_COLUMNS, &ptr_dbManager); // adding spaces to the tableName so that i dont have to add them in the sqliteManager 
  printf("%s", exit ? "Table created successfully\n" : "Something went wrong while creating the table\n");
  
  printf("calling insertAndSaveMeasurements()\n");
  exit = insertAndSaveMeasurements(MEASUREMENTS_TABLE_NAME, &ptr_m, &ptr_dbManager);
  printf("%s", exit ? "Saved successfully\n" : "Something went wrong\n");

  return 0;
}
