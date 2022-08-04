#ifndef REQUESTDATASTRUCT_H
#define REQUESTDATASTRUCT_H

#include<stdbool.h>

#define REQUESTSTRUCT_INITIALIZER {"hourOrDay", "deviceID", "1-1-1111", "1-1-1111"}

typedef struct requestStruct{
  
  char* hourOrDay;
  char* deviceID;
  char* maxLimit;
  char* minLimit;

} requestStruct;

#endif
