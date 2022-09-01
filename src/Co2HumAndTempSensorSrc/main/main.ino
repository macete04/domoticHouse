#include "Net.h"
#include "Dht_Sensor.h"
#include "MQ135_Sensor.h"

const char* ssid     = "your-ssid";
const char* password = "your-password";

const char* mqtt_server = "cow.mq2.cloudamqp.com";
const char* mqtt_us = "your-server-ssid";
const char* mqtt_pass = "your-server-password";
const char* mqtt_id = "your-server-id";
const int   mqtt_port = 1883;

void setup() {
  Serial.begin(9600);
  wifi(ssid, password);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect(mqtt_id, mqtt_us, mqtt_pass);
  }
  client.loop();

  float temp;
  float hum;

  controlloTemp(&hum, &temp);
  mq135(&hum, &temp);
  
}
