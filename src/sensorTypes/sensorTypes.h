#ifndef SENSORTYPES_H
#define SENSORTYPES_H

typedef struct measurements{
  
  char* dateAndHour;
  float temperature;
  float humidity;
  unsigned short int ppmCo2;

}measurements;



#endif
