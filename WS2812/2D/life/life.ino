
#include <OctoWS2811.h>
#define SIZE_X 32
#define SIZE_Y 16

const int ledsPerStrip = 256;
const int ledPin = 13;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

// Cells array
unsigned char lastRound[32][16];
unsigned char life[32][16];
unsigned char nbFrames = 0;

void fillRandom()
{
  int x,y;
  for(x = 0; x < SIZE_X; x++)
  {
    for(y = 0; y < SIZE_Y; y++)
    {
      if(rand() < RAND_MAX/3)
      {
        life[x][y] = 1;
        leds.setPixel(getPos(x,y), 0x0F0F0F);
      }
    }
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  leds.begin();
  fillRandom();
}


unsigned int getPos(unsigned char x, unsigned char y)
{
  if(x%2)
  {
    y = 15-y;
  }
  return x * 16 + y;
}

unsigned char getLastRoundCellWithWrap(unsigned char x, unsigned char y)
{
    return lastRound[x%SIZE_X][y%SIZE_Y];
}

void loop() {
  int x,y,nbChanges,crc;
  digitalWrite(ledPin, HIGH);

  if(nbFrames > 15)
  {
    // Save currentFrame
    memcpy(lastRound, life, sizeof(life));
  
    // Compute next frame
    for(x = 0; x < SIZE_X; x++)
    {
      for(y = 0; y < SIZE_Y; y++)
      {
        // Get neighboor
        unsigned char neigh = getLastRoundCellWithWrap(x-1,y-1) + getLastRoundCellWithWrap(x,y-1) + getLastRoundCellWithWrap(x+1,y-1) + \
                              getLastRoundCellWithWrap(x-1,y) /*+ getLastRoundCellWithWrap(x,y)*/ + getLastRoundCellWithWrap(x+1,y)   + \
                              getLastRoundCellWithWrap(x-1,y+1) + getLastRoundCellWithWrap(x,y+1) + getLastRoundCellWithWrap(x+1,y+1);
        if(lastRound[x][y] && (neigh < 2 || neigh > 3))
        {
          // Dead
          life[x][y] = 0;
          nbChanges++;
        }
        else if(!lastRound[x][y] && neigh == 3)
        {
          // Born
          life[x][y] = 1;
          nbChanges++;
        }
      }
    }
    nbFrames = 0;
  }

  // Update leds
  for(x = 0; x < SIZE_X; x++)
  {
    for(y = 0; y < SIZE_Y; y++)
    {
      if(life[x][y] && !lastRound[x][y])
      {
        leds.setPixel(getPos(x,y), 0x000100 * nbFrames);
      }
      else if(!life[x][y] && lastRound[x][y])
      {
        leds.setPixel(getPos(x,y), 0x010000 * (15-nbFrames));
      }
    }
  }

  digitalWrite(ledPin, LOW);

  leds.show();
  nbFrames++;
}



