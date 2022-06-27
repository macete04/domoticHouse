#include"manager.h"

// definition of "private" functions so that other functions can see them
static void printHello();

bool createDatabase(databaseManager** dbManager){
  
  sqlite3* db;
  
  databaseManager* temp = *dbManager;
 
  // creating the directory where the db will be created

  char *tempStringForDir = malloc(strlen(temp->parentDirectory)+strlen(temp->folder));
 
  strcat(tempStringForDir, temp->parentDirectory);
  strcat(tempStringForDir, temp->folder);
  
  struct stat st = {0};
  if(stat(tempStringForDir, &st) == -1){
    mkdir(tempStringForDir, 0700);
  }

  char *dirToCreateDBIn = malloc(strlen(tempStringForDir) + strlen(temp->name)); 
  strcat(dirToCreateDBIn, tempStringForDir);
  strcat(dirToCreateDBIn, temp->name);
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
  databaseManager *temp = *dbManager;
  
  short int stringLength = strlen(temp->parentDirectory) + strlen(temp->folder) + strlen(temp->name);
  char *tmp_dirWhereDbIsSaved = malloc(stringLength);

  // cleaning memory
  memset(tmp_dirWhereDbIsSaved, 0, stringLength);
  
  // creating string
  strcat(tmp_dirWhereDbIsSaved, temp->parentDirectory);
  strcat(tmp_dirWhereDbIsSaved, temp->folder);
  strcat(tmp_dirWhereDbIsSaved, temp->name);
  
  short int exit = 0;
  exit = sqlite3_open(tmp_dirWhereDbIsSaved, &db);
  
  if(exit != SQLITE_OK){
    return DB_FAIL;
  }

  short int totalLength = 0;
  for(short int i = 0; i < sizeOfArray; ++i){
    totalLength += strlen(colAndTypes[i]);    
  }
  
  char* sqlInstructionStartingPoint = "CREATE TABLE IF NOT EXISTS";
  short int sqlInstructionLength = strlen(tableName) + totalLength + strlen(sqlInstructionStartingPoint) + 2 + (sizeOfArray - 1); // 2 = number of round parenthesis, sizeOfArray - 1 is the number of commas we need
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
      strcat(sqlInstruction, ",");
    }
  }
  strcat(sqlInstruction, ");");
  
  // creating table
  char* errorMessage;
  exit = sqlite3_exec(db, sqlInstruction, NULL, 0, &errorMessage);
  if(exit != SQLITE_OK){
    printf("%s", errorMessage);
    sqlite3_free(errorMessage);
    sqlite3_close(db);
    free(tmp_dirWhereDbIsSaved);
    free(sqlInstruction);
    return DB_FAIL;
  }
  // closing db connection and freeing memory
  sqlite3_close(db);
  
  free(tmp_dirWhereDbIsSaved);
  free(sqlInstruction);
  
  return DB_SUCCESS;
}

// actual developing of "private" functions
static void printHello(){
  
  // do something

}
