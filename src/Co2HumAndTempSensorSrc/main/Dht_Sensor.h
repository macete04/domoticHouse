#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <DHT.h>

#define DHTTYPE DHT22
#define DHTPIN1 3  // pin dht 

DHT dht(DHTPIN1, DHTTYPE);

void controlloTemp(float *hum, float *temp);

#endif
