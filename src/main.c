#include<stdio.h>
#include<stdlib.h>
#include"sqliteManager/manager.h"
#include"sensorTypes/sensorTypes.h"


#define NUMBER_OF_COLUMNS 2


int main(){
  
  // creating db struct
  databaseManager dbManager = {"/database.db", getenv("HOME"), "/NetAtmoOpenSourceUtilities"};
  databaseManager *ptr_dbManager = &dbManager;
  
  measurements m = {"ciao", 12.5, 15.5, 123};
  measurements *ptr_m = &m;

  bool exit;

  exit = createDatabase(&ptr_dbManager);
  
  printf("%s", exit ? "Database created successfully\n" : "Something went wrong while creating the DB\n");
  
  // creating table
  char *columnsAndTypes[NUMBER_OF_COLUMNS] = {"DATO1 TEXT", "DATO2 TEXT"};
  exit = createTable(" tavolaDiProva ", columnsAndTypes, NUMBER_OF_COLUMNS, &ptr_dbManager); // adding spaces to the tableName so that i dont have to add them in the sqliteManager
  
  printf("%s", exit ? "Table created successfully\n" : "Something went wrong while creating the table\n");
  
  insertIntoDbAndSave(" tavolaDiProva ", columnsAndTypes, &ptr_m, &ptr_dbManager);
  return 0;
}
