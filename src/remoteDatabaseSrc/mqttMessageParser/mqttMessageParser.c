#include"mqttMessageParser.h"


#ifndef HOUR
#define HOUR "hour"
#endif 

#ifndef DATE
#define DATE "date"
#endif
void* mqttMessageParser(void* mqttMessage){
  
  databaseManager dbManager = DATABASE_MANAGER_INITIALIZER;
  databaseManager* ptr_dbManager = &dbManager;

  measurements measurementsStruct = MEASUREMENTS_STRUCT_INITIALIZER;
  measurements* ptr_measurementsStruct = &measurementsStruct;
  
  requestStruct requestDataStruct = REQUESTSTRUCT_INITIALIZER;
  requestStruct* ptr_requestDataStruct = &requestDataStruct;
  
  fetchedData dataInDb;
  fetchedData* ptr_dataInDb = &dataInDb;

  char* mqttMessage1 = (char*)mqttMessage;
  
  bool exit;  
  
  printf("%s\n", mqttMessage1);

  if(isRequest(mqttMessage1)){

    getValuesForRequest(mqttMessage1, &ptr_requestDataStruct);
    printf("Message IS a request\n");
   
    // HOUR and DATE defined in jsonManager.h
    if(strcmp(requestDataStruct.hourOrDay, HOUR) == 0){

      getTempHumidityOrCo2Data(&ptr_dbManager, &ptr_dataInDb, SELECT_HOUR_COLUMN, requestDataStruct.chosenParameter, MEASUREMENTS_TABLE, requestDataStruct.minLimit, requestDataStruct.maxLimit);
    
    }else if(strcmp(requestDataStruct.hourOrDay, DATE) == 0){
   
      getTempHumidityOrCo2Data(&ptr_dbManager, &ptr_dataInDb, SELECT_DATE_COLUMN, requestDataStruct.chosenParameter, MEASUREMENTS_TABLE, requestDataStruct.minLimit, requestDataStruct.maxLimit);
    
    }else{
      return false;
    }
  }else{

    getValuesFromMessage(mqttMessage1, &ptr_measurementsStruct);
        
    exit = insertAndSaveMeasurements(MEASUREMENTS_TABLE, &ptr_measurementsStruct, &ptr_dbManager);
    assert(exit == DB_SUCCESS);
  }
}
