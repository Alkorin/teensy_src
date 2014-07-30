#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9340.h>
#include "asciiquarium.h"

#define ASCIIQUARIUM

#define __CS 10
#define __DC 9

TFT_ILI9340 tft = TFT_ILI9340(__CS, __DC);

void setup() {
  tft.begin();
  tft.setBitrate(24000000);
  
  asciiquarium_init();
  
  tft.setRotation(1);
  tft.setTextColor(0xFFFF,0x0000);
}

void loop(void) {
  
//  unsigned int startTime = micros();
  asciiquarium();
//  unsigned int endTime = micros();

//  tft.setCursor(0, 232);
//  tft.printf("%06d", endTime - startTime);
}

