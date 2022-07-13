#ifndef SENSORTYPES_H
#define SENSORTYPES_H

typedef struct measurements{
  
  char* dateOfMeasurement;
  unsigned short int hourOfMeasurement;
  float temperature;
  float humidity;
  unsigned short int ppmCo2;

}measurements;

#endif
