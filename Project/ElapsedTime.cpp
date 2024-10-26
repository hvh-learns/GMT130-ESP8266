#include <cstdio>

#include "ElapsedTime.h"
#include <iostream>  // header in standard library

#define MILLI_SENCOND_PER_SEC 1000
#define MILLI_SENCOND_PER_MIN 60000
#define MILLI_SENCOND_PER_HOUR 3600000
#define MILLI_SENCOND_PER_DAY 86400000

using namespace MyApp;
using namespace std;

MyApp::ElapsedTime::ElapsedTime(unsigned long time_now) {
  this->time_now = time_now;
}

char* MyApp::ElapsedTime::getTime() {
  char result[9];  //00:00:00\0
  unsigned long day, hour, min, sec;
  this->convertMilliSeconds(&day, &hour, &min, &sec);
  if (day == 0) {
    sprintf(result, "%2s:%2s:%2s", this->getTwoDigit(day), this->getTwoDigit(hour), this->getTwoDigit(min));
  } else {
    sprintf(result, "%2s:%2s:%2s", this->getTwoDigit(hour), this->getTwoDigit(min), this->getTwoDigit(sec));
  }
  return result;
}

char* MyApp::ElapsedTime::getTwoDigit(unsigned long number) {
  char result[3];
  if (number < 10) {
    sprintf(result, "0%1d", number);
  } else {
    sprintf(result, "%2d", number);
  }
  return result;
}

void MyApp::ElapsedTime::convertMilliSeconds(unsigned long* day, unsigned long* hour, unsigned long* min, unsigned long* sec) {
  *day = this->time_now / MILLI_SENCOND_PER_DAY;
  *hour = (this->time_now % MILLI_SENCOND_PER_DAY) / MILLI_SENCOND_PER_HOUR;
  *min = (this->time_now % MILLI_SENCOND_PER_DAY % MILLI_SENCOND_PER_HOUR) / MILLI_SENCOND_PER_MIN;
  *sec = (this->time_now % MILLI_SENCOND_PER_DAY % MILLI_SENCOND_PER_HOUR % MILLI_SENCOND_PER_MIN) / MILLI_SENCOND_PER_SEC;
}
