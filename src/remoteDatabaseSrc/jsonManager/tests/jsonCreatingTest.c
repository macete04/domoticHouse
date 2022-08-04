#include<stdio.h>
#include<json-c/json.h>


/*
 * obiettivo json:
 * {
 *  "date" : "12-07-2022", 
 *  "hour" : 14, 
 *  "measurements":{
 *      "temperature" : 27.5, 
 *      "humidity" : 65.7,
 *      "co2" : 234
 *  }
 * }*/


int main(void){
  
  json_object *obj = json_object_new_object();

  json_object_object_add(obj, "date", json_object_new_string("12-97-2022"));
  json_object_object_add(obj, "hour", json_object_new_int(14));

  json_object *measurements = json_object_new_object();
  json_object_object_add(measurements, "temperature", json_object_new_double(27.5));
  json_object_object_add(measurements, "humidity", json_object_new_double(65.7));
  json_object_object_add(measurements, "co2", json_object_new_int(234));
   
  json_object_object_add(obj, "measurements", measurements);

  printf("The json representation:\n\n%s\n\n", json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY));
  
  // cleans everything
  json_object_put(obj);

  return 0;
}
