
#include <OctoWS2811.h>
#define SIZE_X 32
#define SIZE_Y 16

const int ledsPerStrip = 256;
const int ledPin = 13;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

// Current snake position
typedef struct
{
  unsigned char x;
  unsigned char y;
} pos;

pos snake[32];
unsigned char snakeLen;

void setup() {
  pinMode(ledPin, OUTPUT);

  leds.begin();
  snake[0].x = 8;
  snake[0].y = 8;
  snakeLen = 1;  
}


unsigned int getPos(unsigned char x, unsigned char y)
{
  if(x%2)
  {
    y = 15-y;
  }
  return x * 16 + y;
}

void loop() {
  digitalWrite(ledPin, HIGH);

  digitalWrite(ledPin, LOW);

  leds.show();
}



