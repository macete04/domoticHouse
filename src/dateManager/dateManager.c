#include"dateManager.h"

char* getDate(void){

  char* c_day = malloc(sizeof(int));
  char* c_month = malloc(sizeof(int));
  char* c_year = malloc(sizeof(int));
  
  time_t gd_time;
  time(&gd_time);
  
  struct tm local = *localtime(&gd_time);
  
  short int day = local.tm_mday;
  short int month = local.tm_mon + 1;
  short int year = local.tm_year + 1900;
  
  snprintf(c_day, sizeof(int) + 1, "%d", day);
  snprintf(c_month, sizeof(int) + 1, "%d", month);
  snprintf(c_year, sizeof(int) + 1, "%d", year);
  
  short int dateLength = (3 * sizeof(int)) + 2; // 2 = number of "-"
  
  char* date = malloc(dateLength);
  
  memset(date, 0, dateLength);
  
  strcat(date, c_day);
  strcat(date, "-");
  strcat(date, c_month);
  strcat(date, "-");
  strcat(date, c_year);
  
  free(c_day);
  free(c_month);
  free(c_year);

  return date; // not freeing -> mem leak?
}
