#include "Json.h"

void json(float *hum, float *temp, float *rzero, float *correctedRZero, float *resistance, float *ppm, float *correctedPPM){
  doc["Temperature"] = *temp;
  doc["Humidity"] = *hum;
  doc["rzero"] = *rzero;
  doc["correctedRZero"] = *correctedRZero;
  doc["resistance"] = *resistance;
  doc["ppm"] = *ppm;
  doc["correctedPPM"] = *correctedPPM;
}
