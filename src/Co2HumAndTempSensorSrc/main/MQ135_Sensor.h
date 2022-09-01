#ifndef MQ135_SENSOR_H
#define MQ135_SENSOR_H

#include <MQ135.h>

#define PIN_MQ135 A0

MQ135 mq135_sensor(PIN_MQ135);

void mq135(float *hum, float *temp);

#endif
