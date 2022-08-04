#include"mqttMessageParser.h"

void* mqttMessageParser(void* mqttMessage){
  
  databaseManager dbManager = DATABASE_MANAGER_INITIALIZER;
  databaseManager* ptr_dbManager = &dbManager;

  measurements measurementsStruct = MEASUREMENTS_STRUCT_INITIALIZER;
  measurements* ptr_measurementsStruct = &measurementsStruct;
  
  requestStruct requestDataStruct = REQUESTSTRUCT_INITIALIZER;
  requestStruct* ptr_requestDataStruct = &requestDataStruct;
  
  char* mqttMessage1 = (char*)mqttMessage;
  
  bool exit;  
  
  printf("%s\n", mqttMessage1);

  if(isRequest(mqttMessage1)){

    getValuesForRequest(mqttMessage1, &ptr_requestDataStruct);
    printf("Message IS a request\n");

    printf("%s\n", requestDataStruct.hourOrDay);
    printf("%s\n", requestDataStruct.deviceID);
    printf("%s\n", requestDataStruct.maxLimit);
    printf("%s\n", requestDataStruct.minLimit);
      
    // TODO: save info in the db
  }else{

    getValuesFromMessage(mqttMessage1, &ptr_measurementsStruct);
        
    exit = insertAndSaveMeasurements(MEASUREMENTS_TABLE, &ptr_measurementsStruct, &ptr_dbManager);
    assert(exit == DB_SUCCESS);
  }
}
