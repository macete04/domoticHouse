#include"manager.h"

// definition of "private" functions so that other functions can see them
static char* createDbDirectory(databaseManager** dbManager);

bool createDatabase(databaseManager** dbManager){
  
  sqlite3* db;
  
  databaseManager* temp = *dbManager;
 
  // creating the directory where the db will be created
  size_t stringForDirLen = strlen(temp->parentDirectory) + strlen(temp->folder);
  char *tempStringForDir = malloc(stringForDirLen); 
  
  memset(tempStringForDir, 0, stringForDirLen); 
  
  strcat(tempStringForDir, temp->parentDirectory);
  strcat(tempStringForDir, temp->folder);
  
  struct stat st = {0};
  if(stat(tempStringForDir, &st) == -1){
    mkdir(tempStringForDir, 0700);
  }
  
  // creating database
  char *dirToCreateDBIn = createDbDirectory(&temp);
  
  short int exit = 0;
  
  exit = sqlite3_open(dirToCreateDBIn, &db);
  
  // closing db connection and freeing memory
  sqlite3_close(db);
  free(tempStringForDir);
  free(dirToCreateDBIn);

  if(exit != SQLITE_OK){
    return DB_FAIL;
  }
  
  return DB_SUCCESS;
}

bool createTable(char* tableName, char** colAndTypes, short int sizeOfArray, databaseManager** dbManager){
  
  sqlite3 *db;
  databaseManager *tmp_dbManager = *dbManager;
   
  char *tmp_dirWhereDbIsSaved = createDbDirectory(&tmp_dbManager);
  
  short int exit = 0;
  exit = sqlite3_open(tmp_dirWhereDbIsSaved, &db);
  
  if(exit != SQLITE_OK){
    free(tmp_dirWhereDbIsSaved);
    sqlite3_close(db);
    return DB_FAIL;
  }

  short int totalLength = 0;
  for(short int i = 0; i < sizeOfArray; ++i){
    totalLength += strlen(colAndTypes[i]);    
  }
  
  char* sqlInstructionStartingPoint = "CREATE TABLE IF NOT EXISTS";
  short int sqlInstructionLength = strlen(tableName) 
    + totalLength 
    + strlen(sqlInstructionStartingPoint) 
    + 2 
    + 2*((sizeOfArray - 1)); 
  // 2 = number of round parenthesis, sizeOfArray - 1 is the number of commas we need
  // it is multiplied by to to count the spaces that follow the commas.
  
  char *sqlInstruction = malloc(sqlInstructionLength); 
  
  // cleaning memory
  memset(sqlInstruction, 0, sqlInstructionLength);
  
  // creating string
  strcat(sqlInstruction, sqlInstructionStartingPoint);
  strcat(sqlInstruction, tableName);
  strcat(sqlInstruction, "(");
  for(short int i = 0; i < sizeOfArray; ++i){
    strcat(sqlInstruction, colAndTypes[i]);
    if(i != sizeOfArray - 1){
      strcat(sqlInstruction, ", ");
    }
  }
  strcat(sqlInstruction, ");");
  
  // creating table
  char* errorMessage;
  exit = sqlite3_exec(db, sqlInstruction, NULL, 0, &errorMessage);
  sqlite3_close(db);
  free(sqlInstruction);
  free(tmp_dirWhereDbIsSaved);
  if(exit != SQLITE_OK){
    printf("createTable(): Something went wrong: %s\n", errorMessage);
    sqlite3_free(errorMessage);
    return DB_FAIL;
  }
  
  return DB_SUCCESS;
}

bool insertAndSaveMeasurements(char* tableToSaveTo, measurements** measurementsToSave, databaseManager** dbManager){
  
  sqlite3* db;
  databaseManager* tmp_dbManager = *dbManager;
  measurements* tmp_measurementsToSave = *measurementsToSave;
  
  const char* SQL_INSTRUCTION_STARTING_POINT = "INSERT INTO";
  const char* VALUES_STRING = "VALUES";
  
  char* tmp_temperature = malloc(sizeof(double));
  char* tmp_humidity = malloc(sizeof(double));
  char* tmp_co2 = malloc(sizeof(int));
  
  // inserting data in strings so that i can insert them in the main sql instruction
  snprintf(tmp_temperature, sizeof(double) + 1, "%f", tmp_measurementsToSave->temperature);
  snprintf(tmp_humidity, sizeof(double) + 1, "%f", tmp_measurementsToSave->humidity);
  snprintf(tmp_co2, sizeof(int) + 1, "%d", tmp_measurementsToSave->ppmCo2);

  short int sqlInstructionLength = strlen(SQL_INSTRUCTION_STARTING_POINT) 
    + strlen(tableToSaveTo) 
    + strlen(VALUES_STRING) 
    + strlen(tmp_measurementsToSave->dateAndHour)
    + (2*(short int)sizeof(double))
    + (short int)sizeof(int)
    + 4 + 2 + 6 + 2; // in order: number of commas between values and the semicolon at the end of the statement, number of parenthesis, number of ' used
  
  char* sqlInstruction = malloc(sqlInstructionLength);
  
  // cleaning memory
  memset(sqlInstruction, 0, sqlInstructionLength);
  
  // creating the string
  strcat(sqlInstruction, SQL_INSTRUCTION_STARTING_POINT);
  strcat(sqlInstruction, tableToSaveTo);
  strcat(sqlInstruction, VALUES_STRING);
  strcat(sqlInstruction, "(");
  strcat(sqlInstruction, "'");
  strcat(sqlInstruction, tmp_measurementsToSave->dateAndHour);
  strcat(sqlInstruction, "'");
  strcat(sqlInstruction, ", ");
  strcat(sqlInstruction, tmp_temperature);
  strcat(sqlInstruction, ", ");
  strcat(sqlInstruction, tmp_humidity);
  strcat(sqlInstruction, ", ");
  strcat(sqlInstruction, tmp_co2);
  strcat(sqlInstruction, ");");
  
  short int exit = 0;
  exit = sqlite3_open(createDbDirectory(&tmp_dbManager), &db); 
  if(exit != SQLITE_OK){
    sqlite3_close(db);
    free(tmp_temperature);
    free(tmp_humidity);
    free(tmp_co2);
    free(sqlInstruction);
    return DB_FAIL;
  }
  
  char* errorMessage;
  exit = sqlite3_exec(db, sqlInstruction, NULL, 0, &errorMessage);

  free(tmp_temperature);
  free(tmp_humidity);
  free(tmp_co2);
  free(sqlInstruction);
  
  if(exit != SQLITE_OK){
    printf("insertAndSaveMeasurements(): %s\n", errorMessage);
    sqlite3_free(errorMessage);
    return DB_FAIL;
  }
  sqlite3_close(db);

  return DB_SUCCESS;
}

// actual developing of "private" functions
static char* createDbDirectory(databaseManager** dbManager){

  databaseManager* tmp_dbManager = *dbManager;
  
  short int directoryLength = strlen(tmp_dbManager->parentDirectory) + strlen(tmp_dbManager->folder) + strlen(tmp_dbManager->name);
  
  char* tmp_dirWhereDbIsSaved = malloc(directoryLength);
  
  // cleaning memory 
  memset(tmp_dirWhereDbIsSaved, 0, directoryLength);

  strcat(tmp_dirWhereDbIsSaved, tmp_dbManager->parentDirectory);
  strcat(tmp_dirWhereDbIsSaved, tmp_dbManager->folder);
  strcat(tmp_dirWhereDbIsSaved, tmp_dbManager->name);
  
  return tmp_dirWhereDbIsSaved;
}
