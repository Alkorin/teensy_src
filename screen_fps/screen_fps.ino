#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

#define __CS 10
#define __DC 9

TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC);

void setup() {
  tft.begin();
  tft.setBitrate(24000000);
  tft.setRotation(2);
  
  tft.setTextColor(0xFFFF,0x0000);
} 

void loop() {
  unsigned int newTime = micros();
  tft.setCursor(0, 0);
  /*tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");
  tft.print("012345678901234567890");*/
  tft.printf("%06d", micros() - newTime);
}
