#ifndef SENSORTYPES_H
#define SENSORTYPES_H

#define MEASUREMENTS_STRUCT_INITIALIZER {"1-1-1111", 12, "deviceID", 30.7, 70.3, 234}

typedef struct measurements{
  
  char* dateOfMeasurement;
  unsigned short int hourOfMeasurement;
  char* deviceID;
  float temperature;
  float humidity;
  unsigned short int ppmCo2;

}measurements;

#endif
