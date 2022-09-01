#include <DHT.h>

#define DHTTYPE DHT22
#define DHTPIN1 3  // pin dht 

DHT dht(DHTPIN1, DHTTYPE);

void controlloTemp(float *hum, float *temp);

void controlloTemp(float *hum, float *temp){
  *hum = dht.readHumidity();
  
  delay(500);
  
  *temp = dht.readTemperature(); // Read temperature as Celsius (the default)
  
  //client.publish("your-topic", *temp);
  //delay(100);
  //client.publish("your-topic", *hum);
}
