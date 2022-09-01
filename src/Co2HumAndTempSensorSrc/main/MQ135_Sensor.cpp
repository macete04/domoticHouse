#include "MQ135_Sensor.h"

void mq135(float *hum, float *temp){
  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(*temp, *hum);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(*temp, *hum);

  /*client.publish("your-topic", rzero);
  delay(50);
  client.publish("your-topic", correctedRZero);
  delay(50);
  client.publish("your-topic", resistance); rimuovi
  delay(50);
  client.publish("your-topic", ppm);
  delay(50);
  client.publish("your-topic", correctedPPM);
  delay(300);*/
}
