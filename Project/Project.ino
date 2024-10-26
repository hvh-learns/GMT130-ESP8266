#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include "ElapsedTime.h"

using namespace MyApp;

#define TFT_WIDTH 240
#define TFT_HEIGHT 240

// ST7789 TFT module connections
#define TFT_DC 5   // TFT DC  pin is connected to NodeMCU pin D1 (GPIO5)
#define TFT_RST 4  // TFT RST pin is connected to NodeMCU pin D2 (GPIO4)
#define TFT_CS 15  // TFT CS  pin is connected to NodeMCU pin D8 (GPIO15)

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

// #define MILLI_SENCOND_PER_SEC 1000
// #define MILLI_SENCOND_PER_MIN 60000
// #define MILLI_SENCOND_PER_HOUR 3600000
// #define MILLI_SENCOND_PER_DAY 86400000

// initialize ST7789 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)
Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

GFXcanvas1 canvas(164, 30);  // 1-bit, 120x30 pixels

int period = 1000;
unsigned long time_now = 0;

void setup() {
  Serial.begin(9600);
  if (!Serial) delay(3000);

  display.init(TFT_WIDTH, TFT_HEIGHT, SPI_MODE3);
  display.setRotation(2);
  display.fillScreen(WHITE);

  canvas.setFont(&DSEG7_Classic_Bold_30);  // Use custom font and
  canvas.setTextSize(1);
  canvas.setTextWrap(false);  // clip text to canvas

  
}

void loop() {
  if ((unsigned long)(millis() - time_now) > period) {
    time_now = millis();
    MyApp::ElapsedTime elapsedTime(time_now);
    showElapsedTime(elapsedTime.getTime());
  }
}

// void getTimeFromElapsedMillis(unsigned long *day, unsigned long *hour, unsigned long *min, unsigned long *sec) {
//   *day = time_now / MILLI_SENCOND_PER_DAY;
//   *hour = (time_now % MILLI_SENCOND_PER_DAY) / MILLI_SENCOND_PER_HOUR;
//   *min = (time_now % MILLI_SENCOND_PER_DAY % MILLI_SENCOND_PER_HOUR) / MILLI_SENCOND_PER_MIN;
//   *sec = (time_now % MILLI_SENCOND_PER_DAY % MILLI_SENCOND_PER_HOUR % MILLI_SENCOND_PER_MIN) / MILLI_SENCOND_PER_SEC;
// }

// void getTwoDigit(unsigned long number, char* buf) {
//   if (number < 10) {
//     sprintf(buf, "0%1d", number);
//   } else {
//     sprintf(buf, "%2d", number);
//   }
// }

// void getElapsedTime(unsigned long day, unsigned long hour, unsigned long min, unsigned long sec, char* buf) {
//   char bufHour[3];
//   char bufMin[3];
//   getTwoDigit(hour, bufHour);
//   getTwoDigit(min, bufMin);
//   if(day != 0) {
//     char bufDay[3];
//     getTwoDigit(day, bufDay);
//     sprintf(buf, "%2s:%2s:%2s", bufDay, bufHour, bufMin);
//   } else {
//     char bufSec[3];
//     getTwoDigit(sec, bufSec);
//     sprintf(buf, "%2s:%2s:%2s", bufHour, bufMin, bufSec);
//   }
// }

void showElapsedTime(char* time) {

  canvas.fillScreen(0);  // Clear canvas (not display)
  
  canvas.setCursor(0, 30);  // Pos. is BASE LINE when using fonts!
  canvas.print(time);        // Print elapsed time in milliseconds
  // canvas.drawRect(0, 0, canvas.width(), canvas.height(), RED);

  display.drawBitmap(36, 5, canvas.getBuffer(),
                     canvas.width(), canvas.height(), BLACK, WHITE);
}
