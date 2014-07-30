#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9340.h>

#define __CS 10
#define __DC 9
#define __RST 14

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

TFT_ILI9340 tft = TFT_ILI9340(__CS, __DC);

void setup() {
  tft.begin();
  tft.setBitrate(24000000);
  tft.fillScreen(0);
  
  tft.setRotation(1);
  tft.setTextColor(0xFFFF,0x0000);
}

void loop(void) {
  testText();
}

void testText() {
  tft.setCursor(40, 80);
  
  tft.setTextColor(RED);  
  tft.setTextSize(10);
  tft.println("25.4");
}


