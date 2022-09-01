#include "Dht_Sensor.h"

void controlloTemp(float *hum, float *temp){
  *hum = dht.readHumidity();
  
  delay(500);
  
  *temp = dht.readTemperature(); // Read temperature as Celsius (the default)
  
  //client.publish("your-topic", *temp);  //da togliere
  //delay(100);
  //client.publish("your-topic", *hum);
}
