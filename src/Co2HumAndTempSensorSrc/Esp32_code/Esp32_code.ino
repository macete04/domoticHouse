#include "Net.h"
#include "Dht_Sensor.h"
#include "MQ135_Sensor.h"

void setup() {
  Serial.begin(9600);
  wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temp;
  float hum;

  controlloTemp(&hum, &temp);
  mq135(&hum, &temp);
  
}
