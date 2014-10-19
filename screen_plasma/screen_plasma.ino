#include <SPI.h>
#include <ILI9341_t3.h>

#define PLASMA

#define __CS 10
#define __DC 9

ILI9341_t3 tft = ILI9341_t3(__CS, __DC);

void setup() {
  tft.begin();
  tft.setRotation(0);
  tft.setTextColor(0xFFFF, 0x0000);
}

void loop(void) {
  //unsigned int startTime = micros();
  plasma1();
  //unsigned int endTime = micros();

  //tft.setCursor(0, 312);
  //tft.printf("%06d", endTime - startTime);
}

