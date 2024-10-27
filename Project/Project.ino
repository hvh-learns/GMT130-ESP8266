#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include <cstring>
#include "7seg20.h"
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

// initialize ST7789 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)
Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

GFXcanvas1 canvas(60, 30);  // 1-bit, 120x30 pixels

int period = 1000;
unsigned long time_now = 0;

char posOne[3];
char posTwo[3];
char posThree[3];

void setup() {
  Serial.begin(9600);
  if (!Serial) delay(3000);

  display.init(TFT_WIDTH, TFT_HEIGHT, SPI_MODE3);
  display.setRotation(2);
  display.fillScreen(WHITE);

  canvas.setFont(&DSEG7_Classic_Bold_30);  // Use custom font and
  canvas.setTextSize(1);
  canvas.setTextWrap(false);  // clip text to canvas

  // canvas.drawRect(0, 0, canvas.width(), canvas.height(), RED);

  // display.drawBitmap(36, 5, canvas.getBuffer(), canvas.width(), canvas.height(), BLACK, WHITE);
}

void loop() {

  if ((unsigned long)(millis() - time_now) > period) {
    time_now = millis();
    char posOneTmp[3], posTwoTmp[3], posThreeTmp[3];
    MyApp::ElapsedTime elapsedTime(time_now);
    elapsedTime.getTime(posOneTmp, posTwoTmp, posThreeTmp);
    showElapsedTime(posOneTmp, posTwoTmp, posThreeTmp);
  }
}

void showElapsedTime(char* posOneTmp, char* posTwoTmp, char* posThreeTmp) {

  int16_t x1, y1;
  uint16_t w, h;

  if (strcmp(posOneTmp, posOne) != 0) {
    Serial.println("draw PosOne");
    sprintf(posOne, "%2s", posOneTmp);
    canvas.fillScreen(0);
    canvas.setCursor(0, 30);
    canvas.print(posOne);

    canvas.getTextBounds(posOne, 0, 30, &x1, &y1, &w, &h);
    canvas.drawRect(x1, y1, w, h, RED);

    canvas.drawRect(0, 0, canvas.width(), canvas.height(), RED);

    display.drawBitmap(30, 5, canvas.getBuffer(),
                       canvas.width(), canvas.height(), BLACK, WHITE);
  }
  if (strcmp(posTwoTmp, posTwo) != 0) {
    Serial.println("draw PosTwo");
    sprintf(posTwo, "%2s", posTwoTmp);
    canvas.fillScreen(0);
    canvas.setCursor(0, 30);
    canvas.print(posTwo);

    canvas.getTextBounds(posOne, 0, 30, &x1, &y1, &w, &h);
    canvas.drawRect(x1, y1, w, h, RED);

    canvas.drawRect(0, 0, canvas.width(), canvas.height(), RED);

    display.drawBitmap(90, 5, canvas.getBuffer(),
                       canvas.width(), canvas.height(), BLACK, WHITE);
  }
  if (strcmp(posThreeTmp, posThree) != 0) {
    Serial.println("draw PosThree");
    sprintf(posThree, "%2s", posThreeTmp);
    canvas.fillScreen(0);
    canvas.setCursor(0, 30);
    canvas.print(posThree);

    canvas.getTextBounds(posOne, 0, 30, &x1, &y1, &w, &h);
    canvas.drawRect(x1, y1, w, h, RED);

    canvas.drawRect(0, 0, canvas.width(), canvas.height(), RED);

    display.drawBitmap(150, 5, canvas.getBuffer(),
                       canvas.width(), canvas.height(), BLACK, WHITE);
  }
}
