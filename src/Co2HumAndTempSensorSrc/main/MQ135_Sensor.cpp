#include "MQ135_Sensor.h"

void mq135(float *hum, float *temp, float *rzero, float *correctedRZero, float *resistance, float *ppm, float *correctedPPM){
  *rzero = mq135_sensor.getRZero();
  *correctedRZero = mq135_sensor.getCorrectedRZero(*temp, *hum);
  *resistance = mq135_sensor.getResistance();
  *ppm = mq135_sensor.getPPM();
  *correctedPPM = mq135_sensor.getCorrectedPPM(*temp, *hum);
}
