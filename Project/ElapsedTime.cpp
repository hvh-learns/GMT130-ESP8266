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

void MyApp::ElapsedTime::getTime(char *posOne, char *posTwo, char *posThree) {
  unsigned long day, hour, min, sec;
  this->convertMilliSeconds(&day, &hour, &min, &sec);
  if (day != 0) {
    this->getTwoDigit(day, posOne);
    this->getTwoDigit(hour, posTwo);
    this->getTwoDigit(min, posThree);
  } else {
    this->getTwoDigit(hour, posOne);
    this->getTwoDigit(min, posTwo);
    this->getTwoDigit(sec, posThree);
  }
}

void MyApp::ElapsedTime::getTwoDigit(unsigned long number, char *output) {
  if (number < 10) {
    sprintf(output, "0%1d", number);
  } else {
    sprintf(output, "%2d", number);
  }
}

void MyApp::ElapsedTime::convertMilliSeconds(unsigned long* day, unsigned long* hour, unsigned long* min, unsigned long* sec) {
  *day = this->time_now / MILLI_SENCOND_PER_DAY;
  *hour = (this->time_now % MILLI_SENCOND_PER_DAY) / MILLI_SENCOND_PER_HOUR;
  *min = (this->time_now % MILLI_SENCOND_PER_DAY % MILLI_SENCOND_PER_HOUR) / MILLI_SENCOND_PER_MIN;
  *sec = (this->time_now % MILLI_SENCOND_PER_DAY % MILLI_SENCOND_PER_HOUR % MILLI_SENCOND_PER_MIN) / MILLI_SENCOND_PER_SEC;
}
