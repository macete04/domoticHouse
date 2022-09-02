#ifndef JSON_H
#define JSON_H

#include <ArduinoJson.h>

DynamicJsonDocument doc(1024);

void json(float *hum, float *temp, float *rzero, float *correctedRZero, float *resistance, float *ppm, float *correctedPPM);

#endif
