#include <OctoWS2811.h>

const int ledsPerStrip = 256;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

const unsigned char ovh[16][16] = {
  { 0xff,0xff,0xff,0xff,0xc8,0x63,0x37,0x12,0x12,0x37,0x63,0xc8,0xff,0xff,0xff,0xff,  },
  { 0xff,0xff,0xdd,0x3d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3d,0xdd,0xff,0xff,  },
  { 0xff,0xc6,0x15,0x00,0x00,0x00,0x1b,0x59,0x59,0x1b,0x00,0x00,0x00,0x15,0xc6,0xff,  },
  { 0xe8,0x10,0x00,0x00,0x3c,0xdb,0xff,0xff,0xff,0xff,0xdb,0x3c,0x00,0x00,0x10,0xe8,  },
  { 0x59,0x00,0x00,0x54,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x54,0x00,0x00,0x59,  },
  { 0x63,0x3b,0x3b,0xb6,0xff,0xff,0xff,0x75,0x3f,0x3f,0xff,0xff,0xb6,0x3b,0x3b,0x63,  },
  { 0xbd,0x00,0x00,0x22,0xff,0xff,0xc1,0x00,0x00,0x1f,0xff,0xff,0x21,0x00,0x00,0xbd,  },
  { 0xff,0x56,0x00,0x00,0x81,0xff,0x2d,0x00,0x00,0x7e,0x57,0x3d,0x00,0x00,0x56,0xff,  },
  { 0xff,0xff,0x0b,0x00,0x09,0x98,0x00,0x00,0x43,0x21,0x00,0x00,0x00,0x0b,0xff,0xff,  },
  { 0xff,0xff,0x87,0x00,0x00,0x4c,0x1d,0x05,0x90,0x37,0x05,0x00,0x00,0x87,0xff,0xff,  },
  { 0xff,0xff,0xff,0x26,0x00,0x00,0x79,0x75,0xff,0xb9,0x00,0x00,0x26,0xff,0xff,0xff,  },
  { 0xc1,0x8f,0x8f,0x87,0xa5,0xa7,0xc4,0xff,0xff,0xc4,0xa7,0xa5,0x88,0x8f,0x8f,0xc1,  },
  { 0xe5,0x14,0x00,0x00,0x3f,0xdf,0xff,0xff,0xff,0xff,0xdf,0x3f,0x00,0x00,0x14,0xe5,  },
  { 0xff,0xc0,0x12,0x00,0x00,0x01,0x26,0x5c,0x5c,0x26,0x01,0x00,0x00,0x12,0xc0,0xff,  },
  { 0xff,0xff,0xe0,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0xe0,0xff,0xff,  },
  { 0xff,0xff,0xff,0xff,0xc6,0x5e,0x31,0x10,0x10,0x31,0x5e,0xc6,0xff,0xff,0xff,0xff,  },
};

unsigned int getPos(unsigned char x, unsigned char y)
{
  if(x%2)
  {
    y = 15-y;
  }
  return x * 16 + y;
}

unsigned int frame = 0;
unsigned int color = 0;
int centerX = 15;
int centerY = 15;

void setup() {
  unsigned char x, y;
  leds.begin();
}

#define MAX_LIGHT 5

void loop() {
  unsigned char x, y;

  /* 1st screen colorized logo */
  for (x = 0; x < 16; x++)
  {
    for (y = 0; y < 16; y++)
    {
      int index = color + ((x*2-centerX)*(x*2-centerX) + (y*2-centerY)*(y*2-centerY))/4;
      leds.setPixel(getPos(x,y),makeColor(index, 100, ((0xFF-ovh[y][(x+(frame>>4))%16]) * MAX_LIGHT ) >> 8));
    }
  }
  color = (color+1) % 360;
  frame++;
  leds.show();
}
