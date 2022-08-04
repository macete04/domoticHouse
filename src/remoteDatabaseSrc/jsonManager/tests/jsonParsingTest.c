#include<stdio.h>
#include"jsonManager.h"


int main(){

  FILE *fp;
  char buffer[1024];

  fp = fopen("jsonFile.json", "r");
  
  fread(buffer, 1024, 1, fp);
  fclose(fp);
  
  measurements m;
  measurements *ptr_m = &m;

  bool exit = getValuesFromMessage(buffer, &ptr_m);
  
  printf("%s\n", m.dateOfMeasurement);
  printf("%s\n", m.deviceID);
  printf("%d\n", m.hourOfMeasurement);
  printf("%f\n", m.temperature);
  printf("%f\n", m.humidity);
  printf("%d\n", m.ppmCo2);
  
  return 0;
}
