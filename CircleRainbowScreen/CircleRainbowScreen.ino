/*  OctoWS2811 Rainbow.ino - Rainbow Shifting Test
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
    Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.


  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.
    pin 1 - Output indicating CPU usage, monitor with an oscilloscope,
            logic analyzer or even an LED (brighter = CPU busier)
*/

#include <OctoWS2811.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

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

float sin_d[] = { 
  0,0.17,0.34,0.5,0.64,0.77,0.87,0.94,0.98,1,0.98,0.94,
  0.87,0.77,0.64,0.5,0.34,0.17,0,-0.17,-0.34,-0.5,-0.64,
  -0.77,-0.87,-0.94,-0.98,-1,-0.98,-0.94,-0.87,-0.77,
  -0.64,-0.5,-0.34,-0.17 };
float cos_d[] = { 
  1,0.98,0.94,0.87,0.77,0.64,0.5,0.34,0.17,0,-0.17,-0.34,
  -0.5,-0.64,-0.77,-0.87,-0.94,-0.98,-1,-0.98,-0.94,-0.87,
  -0.77,-0.64,-0.5,-0.34,-0.17,0,0.17,0.34,0.5,0.64,0.77,
  0.87,0.94,0.98};
float d = 10;
float px[] = { 
  -d,  d,  d, -d, -d,  d,  d, -d };
float py[] = { 
  -d, -d,  d,  d, -d, -d,  d,  d };
float pz[] = { 
  -d, -d, -d, -d,  d,  d,  d,  d };

float p2x[] = {
  0,0,0,0,0,0,0,0};
float p2y[] = {
  0,0,0,0,0,0,0,0};

int r[] = {
  0,0,0};

TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC);

const int ledsPerStrip = 256;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

const int rainbowColors[30] = { 0x00050000,0x00050100,0x00050200,0x00050300,0x00050400,0x00050500,0x00040500,0x00030500,0x00020500,0x00010500,0x00000500,0x00000501,0x00000502,0x00000503,0x00000504,0x00000505,0x00000405,0x00000305,0x00000205,0x00000105,0x00000005,0x00010005,0x00020005,0x00030005,0x00040005,0x00050005,0x00050004,0x00050003,0x00050002,0x00050001 };
void setup() {
  /*for (int i=0; i<30; i++) {
    int hue = i*12;
    int saturation = 100;
    int lightness = 1;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, lightness);
  }*/
  tft.begin();
  tft.setBitrate(24000000);

  leds.begin();
}


unsigned int getPos(unsigned char x, unsigned char y)
{
  if(x%2)
  {
    y = 15-y;
  }
  return x * 16 + y;
}

int centerX = 31;
int centerY = 15;
unsigned int color = 0;
/*float moveX = -0.1;
float moveY = -0;*/
unsigned int l = 0;

void loop() {  color++;
  /for (int x=0; x < 32; x++) {
    for (int y=0; y < 16; y++) {
      int index = color/6 + ((x*2-centerX)*(x*2-centerX) + (y*2-centerY)*(y*2-centerY))/24;
      leds.setPixel(getPos(x,y), rainbowColors[index%30]);
    }
  }
  if(!(l%8))
  { 
    testText();
  }
  leds.show();

  l++;
}

void testText() {
  tft.fillScreen(WHITE);
  r[0]=r[0]+1;
  r[1]=r[1]+1;
  if (r[0] == 36) r[0] = 0;
  if (r[1] == 36) r[1] = 0;
  if (r[2] == 36) r[2] = 0;
  for (int i=0;i<8;i++)
  {
    float px2 = px[i];
    float py2 = cos_d[r[0]]*py[i] - sin_d[r[0]]*pz[i];
    float pz2 = sin_d[r[0]]*py[i] + cos_d[r[0]]*pz[i];

    float px3 = cos_d[r[1]]*px2 + sin_d[r[1]]*pz2;
    float py3 = py2;
    float pz3 = -sin_d[r[1]]*px2 + cos_d[r[1]]*pz2;

    float ax = cos_d[r[2]]*px3 - sin_d[r[2]]*py3;
    float ay = sin_d[r[2]]*px3 + cos_d[r[2]]*py3;
    float az = pz3-190;

    p2x[i] = ((tft.width())/2)+ax*500/az;
    p2y[i] = ((tft.height())/2)+ay*500/az;
  }
  for (int i=0;i<3;i++) {
    tft.drawLine(p2x[i],p2y[i],p2x[i+1],p2y[i+1],BLACK);
    tft.drawLine(p2x[i+4],p2y[i+4],p2x[i+5],p2y[i+5],BLACK);
    tft.drawLine(p2x[i],p2y[i],p2x[i+4],p2y[i+4],BLACK);
  }   
  tft.drawLine(p2x[3],p2y[3],p2x[0],p2y[0],BLACK);
  tft.drawLine(p2x[7],p2y[7],p2x[4],p2y[4],BLACK);
  tft.drawLine(p2x[3],p2y[3],p2x[7],p2y[7],BLACK);
}



