#include<stdio.h>
#include<stdlib.h>
#include"sqliteManager/manager.h"
#include"sensorTypes/sensorTypes.h"
#include"dateManager/dateManager.h"

#define NUMBER_OF_COLUMNS 5


int main(void){
  
  databaseManager dbManager = {"/measurements.db", getenv("HOME"), "/domoticHouseUtilities"};
  databaseManager *ptr_dbManager = &dbManager;
  
  char* todaysDate = getDate();
  measurements m = {todaysDate, 18, 33.7, 52.7, 224};
  measurements *ptr_m = &m;
  
  const char* MEASUREMENTS_TABLE_NAME = " measurementsTable ";

  bool exit;

  exit = createDatabase(&ptr_dbManager);
  
  printf("%s", exit ? "Database created successfully\n" : "Something went wrong while creating the DB\n");
  
  char* columnsAndTypes[NUMBER_OF_COLUMNS] = {"DAYOFMEASUREMENT date", "HOUROFMEASUREMENT INTEGER", "TEMPERATURE REAL", "HUMIDITY REAL", "CO2PPM INTEGER"};
  
  printf("calling createTable()\n");
  exit = createTable(MEASUREMENTS_TABLE_NAME, columnsAndTypes, NUMBER_OF_COLUMNS, &ptr_dbManager); // adding spaces to the tableName so that i dont have to add them in the sqliteManager 
  printf("%s", exit ? "Table created successfully\n" : "Something went wrong while creating the table\n");
  
  printf("calling insertAndSaveMeasurements()\n");
  exit = insertAndSaveMeasurements(MEASUREMENTS_TABLE_NAME, &ptr_m, &ptr_dbManager);
  printf("%s", exit ? "Saved successfully\n" : "Something went wrong\n");
  
  printf("Calling getTempOrHum...()");
  fetchedData fetchedDataFromDb;
  fetchedData* ptr_fetchedDataFromDb = &fetchedDataFromDb;

  exit = getTempOrHumidityDataByHour(&ptr_dbManager, &ptr_fetchedDataFromDb, false, MEASUREMENTS_TABLE_NAME, 14, 16);
  
  printf("contatore: %d\n", fetchedDataFromDb.indexNumber);
  
  for(short int i = 0; i < fetchedDataFromDb.indexNumber; ++i){
    printf("Valore nell'array alla casella %d: %f\n", i, *(fetchedDataFromDb.fetchedDataArray + i));
  }
  free(fetchedDataFromDb.fetchedDataArray); 
  free(todaysDate);
  return 0;
}
