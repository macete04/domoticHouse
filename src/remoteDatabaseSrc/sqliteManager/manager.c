#include"manager.h"

// definition of "private" functions so that other functions can see them (but only in this file)
static char* createDbDirectory(databaseManager** dbManager);

// developing of functions declared in manager.h
bool createDatabase(databaseManager** dbManager){
  
  sqlite3* db;
  
  databaseManager* tmp_dbManager = *dbManager;
 
  // creating the directory where the db will be created
  size_t stringForDirLen = strlen(tmp_dbManager->parentDirectory) + strlen(tmp_dbManager->folder);
  char *tempStringForDir = malloc(stringForDirLen); 
  
  memset(tempStringForDir, 0, stringForDirLen); 
  
  strcat(tempStringForDir, tmp_dbManager->parentDirectory);
  strcat(tempStringForDir, tmp_dbManager->folder);
  
  struct stat st = {0};
  if(stat(tempStringForDir, &st) == -1){
    mkdir(tempStringForDir, 0700);
  }
  
  // creating database
  char *dirToCreateDBIn = createDbDirectory(&tmp_dbManager);
  
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

bool createTable(const char* tableName, char** colAndTypes, short int sizeOfArray, databaseManager** dbManager){
  
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

bool insertAndSaveMeasurements(const char* tableToSaveTo, measurements** measurementsToSave, databaseManager** dbManager){
  
  sqlite3* db;
  databaseManager* tmp_dbManager = *dbManager;
  measurements* tmp_measurementsToSave = *measurementsToSave;
  
  const char* SQL_INSTRUCTION_STARTING_POINT = "INSERT INTO";
  const char* VALUES_STRING = "VALUES";
  
  char* tmp_hourOfMeasurement = malloc(sizeof(int));
  char* tmp_temperature = malloc(sizeof(double));
  char* tmp_humidity = malloc(sizeof(double));
  char* tmp_co2 = malloc(sizeof(int));
  
  // inserting data in strings so that i can insert them in the main sql instruction
  snprintf(tmp_hourOfMeasurement, sizeof(int) + 1, "%d", tmp_measurementsToSave->hourOfMeasurement);
  snprintf(tmp_temperature, sizeof(double) + 1, "%f", tmp_measurementsToSave->temperature);
  snprintf(tmp_humidity, sizeof(double) + 1, "%f", tmp_measurementsToSave->humidity);
  snprintf(tmp_co2, sizeof(int) + 1, "%d", tmp_measurementsToSave->ppmCo2);
  
  short int sqlInstructionLength = strlen(SQL_INSTRUCTION_STARTING_POINT) 
    + strlen(tableToSaveTo) 
    + strlen(VALUES_STRING) 
    + strlen(tmp_measurementsToSave->dateOfMeasurement)
    + strlen(tmp_measurementsToSave->deviceID)
    + (2*(short int)sizeof(double))
    + (2*(short int)sizeof(int))
    + 2 // the two parenthesis that wrap the values
    + 4 // number of ' used
    + 5*2 // number of commas and the space immediately after them
    + 1; // the semicolon at the end of the statement 
  
  char* sqlInstruction = malloc(sqlInstructionLength);
  
  // cleaning memory
  memset(sqlInstruction, 0, sqlInstructionLength);
  
  // creating the string
  strcat(sqlInstruction, SQL_INSTRUCTION_STARTING_POINT);
  strcat(sqlInstruction, tableToSaveTo);
  strcat(sqlInstruction, VALUES_STRING);
  strcat(sqlInstruction, "(");
  strcat(sqlInstruction, "'");
  strcat(sqlInstruction, tmp_measurementsToSave->dateOfMeasurement);
  strcat(sqlInstruction, "'");
  strcat(sqlInstruction, ", ");
  strcat(sqlInstruction, "'");
  strcat(sqlInstruction, tmp_measurementsToSave->deviceID);
  strcat(sqlInstruction, "'");
  strcat(sqlInstruction, ", ");
  strcat(sqlInstruction, tmp_hourOfMeasurement);
  strcat(sqlInstruction, ", ");
  strcat(sqlInstruction, tmp_temperature);
  strcat(sqlInstruction, ", ");
  strcat(sqlInstruction, tmp_humidity);
  strcat(sqlInstruction, ", ");
  strcat(sqlInstruction, tmp_co2);
  strcat(sqlInstruction, ");");
  
  short int exit = 0;
  
  char* tmp_dbDirectory = createDbDirectory(&tmp_dbManager);
  printf("%s\n", tmp_dbDirectory);
  exit = sqlite3_open(tmp_dbDirectory, &db); 
  if(exit != SQLITE_OK){
    sqlite3_close(db);
    free(tmp_hourOfMeasurement);
    free(tmp_temperature);
    free(tmp_humidity);
    free(tmp_co2);
    free(sqlInstruction);
    free(tmp_dbDirectory);
    return DB_FAIL;
  }
  
  char* errorMessage;
  exit = sqlite3_exec(db, sqlInstruction, NULL, 0, &errorMessage);
  
  free(tmp_hourOfMeasurement);
  free(tmp_temperature);
  free(tmp_humidity);
  free(tmp_co2);
  free(sqlInstruction);
  free(tmp_dbDirectory);

  if(exit != SQLITE_OK){
    printf("insertAndSaveMeasurements(...): %s\n", errorMessage);
    sqlite3_free(errorMessage);
    return DB_FAIL;
  }
  sqlite3_close(db);

  return DB_SUCCESS;
}

bool getTempOrHumidityDataByHour(databaseManager** dbManager, fetchedData** fetchedDataFromDb, bool isTemperature, const char* tableName, const unsigned short int minHour, const unsigned short int maxHour){
  
  sqlite3 *db;
  sqlite3_stmt* stmt;
  databaseManager* tmp_dbManager = *dbManager;
  fetchedData* tmp_fetchedDataFromDb = *fetchedDataFromDb;
 
  const char* SQL_INSTRUCTION_STARTING_POINT = "SELECT ";
  const char* SQL_FROM_STRING = " FROM";
  const char* SQL_WHERE_STRING = "WHERE HOUROFMEASUREMENT >= ";
  const char* SQL_AND_STRING = " AND HOUROFMEASUREMENT <= ";
  
  char* tmp_minHour = malloc(sizeof(unsigned short int));
  char* tmp_maxHour = malloc(sizeof(unsigned short int));
  
  char* parameterToSelect = (isTemperature) ? "TEMPERATURE" : "HUMIDITY";

  snprintf(tmp_minHour, sizeof(unsigned short int) + 1, "%d", minHour);
  snprintf(tmp_maxHour, sizeof(unsigned short int) + 1, "%d", maxHour);

  short int sqlInstructionLength = strlen(SQL_INSTRUCTION_STARTING_POINT)
    + strlen(parameterToSelect)
    + strlen(SQL_FROM_STRING)
    + strlen(tableName)
    + strlen(SQL_WHERE_STRING)
    + strlen(tmp_minHour)
    + strlen(SQL_AND_STRING)
    + strlen(tmp_maxHour);
 
  char* sqlInstruction = malloc(sqlInstructionLength);
  
  memset(sqlInstruction, 0, sqlInstructionLength);

  strcat(sqlInstruction, SQL_INSTRUCTION_STARTING_POINT);
  strcat(sqlInstruction, parameterToSelect);
  strcat(sqlInstruction, SQL_FROM_STRING);
  strcat(sqlInstruction, tableName);
  strcat(sqlInstruction, SQL_WHERE_STRING);
  strcat(sqlInstruction, tmp_minHour);
  strcat(sqlInstruction, SQL_AND_STRING);
  strcat(sqlInstruction, tmp_maxHour);
  
  short int exit = 0;

  char* tmp_dbDirectory = createDbDirectory(&tmp_dbManager);
  exit = sqlite3_open(tmp_dbDirectory, &db);
  if(exit != SQLITE_OK){
    sqlite3_close(db);
    free(tmp_minHour);
    free(tmp_maxHour);
    free(sqlInstruction);
    free(tmp_dbDirectory);
    printf("getTempOrHumidityDataByHour(): something went wrong while opening db");
    return DB_FAIL;
  }

  exit = sqlite3_prepare_v2(db, sqlInstruction, -1, &stmt, 0);
  
  if(exit != SQLITE_OK){
    sqlite3_close(db);
    free(tmp_minHour);
    free(tmp_maxHour);
    free(sqlInstruction);
    free(tmp_dbDirectory);
    printf("getTempOrHumidityDataByHour(): something went wrong while reading db");
    return DB_FAIL;
  }
   
  short int counter = 0;
  while(sqlite3_step(stmt) == SQLITE_ROW){counter++;}
  printf("counter: %d\n", counter);
  tmp_fetchedDataFromDb->indexNumber = counter;

  double* fetchedDataContainer = malloc(sizeof(double) * counter);
  
  memset(fetchedDataContainer, 0, counter);

  short int i = 0;   
  while((sqlite3_step(stmt) == SQLITE_ROW)&&(i < counter)){
    printf("sus %d: %f\n", i, sqlite3_column_double(stmt, 0));
    fetchedDataContainer[i] = sqlite3_column_double(stmt, 0);
    i++;
  }

  tmp_fetchedDataFromDb->fetchedDataArray = fetchedDataContainer;

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  free(tmp_minHour);
  free(tmp_maxHour);
  free(sqlInstruction);
  free(tmp_dbDirectory);
  return true;
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
