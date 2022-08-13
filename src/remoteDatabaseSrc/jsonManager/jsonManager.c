#include"jsonManager.h"

bool getInfosFromConfigFile(char* configFile, mqttClientInfos** mqttClientStuff){
  
  mqttClientInfos* tmp_mqttClientStuff = *mqttClientStuff;
  
  json_object *configFileToParse;
  json_object *broker, *clientID, *username, *password, *topics;
  json_object *recvFromDevice1;
  
  configFileToParse = json_tokener_parse(configFile);
  
  broker = json_object_object_get(configFileToParse, "broker");
  clientID = json_object_object_get(configFileToParse, "client_id");
  username = json_object_object_get(configFileToParse, "username");
  password = json_object_object_get(configFileToParse, "password");
  topics = json_object_object_get(configFileToParse, "topics");

  tmp_mqttClientStuff->broker = json_object_get_string(broker);
  tmp_mqttClientStuff->clientID = json_object_get_string(clientID);
  tmp_mqttClientStuff->username = json_object_get_string(username);
  tmp_mqttClientStuff->password = json_object_get_string(password);
  tmp_mqttClientStuff->topicsArrayLength = json_object_array_length(topics);
  
  char** tmp_topics = malloc(256 * tmp_mqttClientStuff->topicsArrayLength); 
  for(short int i = 0; i < tmp_mqttClientStuff->topicsArrayLength; ++i){
    json_object* tmp_singleTopic = json_object_array_get_idx(topics, i);
    tmp_topics[i] = json_object_get_string(tmp_singleTopic);
  }
  tmp_mqttClientStuff->topics = tmp_topics;
  
  return true;
}

bool isRequest(char* message){
	
	json_object *jsonToParse;
	json_object *request;

	jsonToParse = json_tokener_parse(message);
	
	request = json_object_object_get(jsonToParse, "request");
	bool otherRequest = (bool)json_object_get_int(request);
	
  return otherRequest;
}

bool getValuesFromMessage(char* mqttMessage, measurements** measurmentsStruct){
  
  // i dont't really know how to do error checking here...
  // might as well make the function void, but i'll figure something out
  // to be able to error check.

  measurements* tmp_measurementsStruct = *measurmentsStruct;
  json_object *jsonToParse;
  json_object *date, *hour, *device, *measurements;
  json_object *temperature, *humidity, *co2;
  
  jsonToParse = json_tokener_parse(mqttMessage);
  
  date = json_object_object_get(jsonToParse, "date");
  hour = json_object_object_get(jsonToParse, "hour");
  device = json_object_object_get(jsonToParse, "device");
  measurements = json_object_object_get(jsonToParse, "measurements");
  temperature = json_object_object_get(measurements, "temperature");
  humidity = json_object_object_get(measurements, "humidity");
  co2 = json_object_object_get(measurements, "co2");
  
  tmp_measurementsStruct->dateOfMeasurement = json_object_get_string(date);
  tmp_measurementsStruct->hourOfMeasurement = json_object_get_int(hour);
  tmp_measurementsStruct->deviceID = json_object_get_string(device);
  tmp_measurementsStruct->temperature = json_object_get_double(temperature);
  tmp_measurementsStruct->humidity = json_object_get_double(humidity);
  tmp_measurementsStruct->ppmCo2 = json_object_get_int(co2);

  return true;
}

#define DATE "date"
#define HOUR "hour"

bool getValuesForRequest(char* mqttMessage, requestStruct** requestDataStruct){
  
  requestStruct* tmp_requestDataStruct = *requestDataStruct;
  
  json_object *jsonToParse;
  json_object *hourOrDay, *deviceID, *parameterFromJson;
  
  jsonToParse = json_tokener_parse(mqttMessage);

  hourOrDay = json_object_object_get(jsonToParse, "hourOrDay");
  deviceID = json_object_object_get(jsonToParse, "deviceID");
  parameterFromJson = json_object_object_get(jsonToParse, "chosenParameter");
  tmp_requestDataStruct->hourOrDay = json_object_get_string(hourOrDay);
  tmp_requestDataStruct->deviceID = json_object_get_string(deviceID);
  tmp_requestDataStruct->chosenParameter = json_object_get_int(parameterFromJson);

  if(strcmp(tmp_requestDataStruct->hourOrDay, HOUR) == 0){

    json_object* maxHour, *minHour;
    maxHour = json_object_object_get(jsonToParse, "maxHour");
    minHour = json_object_object_get(jsonToParse, "minHour");
    tmp_requestDataStruct->maxLimit = json_object_get_string(maxHour);
    tmp_requestDataStruct->minLimit = json_object_get_string(minHour);
    
  }else if(strcmp(tmp_requestDataStruct->hourOrDay, DATE) == 0){

    json_object *maxDate, *minDate;
    maxDate = json_object_object_get(jsonToParse, "maxDate");
    minDate = json_object_object_get(jsonToParse, "minDate");
    tmp_requestDataStruct->maxLimit = json_object_get_string(maxDate);
    tmp_requestDataStruct->minLimit = json_object_get_string(minDate);

  }
  
  return true; // same thing as per the getValuesFromMessage function.
}
