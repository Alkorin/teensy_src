#include <OctoWS2811.h>

const int ledsPerStrip = 256;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

unsigned int getPos(unsigned char x, unsigned char y)
{
  if(x%2 == 0)
  {
    y = 15-y;
  }
  return x * 16 + y;
}

int centerX = 31;
int centerY = 0;

void setup() {
  unsigned char x, y;
  leds.begin();
}

void loop() {
  static int frame = 0;
  unsigned char x, y, r;
  
  frame++;

  memset(drawingMemory, 0, sizeof(drawingMemory));
  
  for (r = 8; r < 16; r++)
  {
    for (x = 0; x < 32; x++)
    {
      for (y = 0; y < 16; y++)
      {
        unsigned int distance = (x*2 - centerX)*(x*2 - centerX) + (y*2 - centerY)*(y*2 - centerY);
        if(distance >= (2*r)*(2*r) && distance <= (2*(r+1))*(2*(r+1)))
        {
          leds.setPixel(getPos(x,y), makeColor(frame+r*32,100,2));
        }
      }
    }
  }
  
  leds.show();
}

