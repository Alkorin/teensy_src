#include <OctoWS2811.h>

const int ledsPerStrip = 16;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

OctoWS2811 Leds(ledsPerStrip, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

int lastTime;
float leds[ledsPerStrip];

void setup() {
  Leds.begin();
  Serial.begin(9600);
}


void loop() {
  for (int i = 1; i <31; i++)
  {
    int ledNumberOn = abs(i-16);

    // Slow down all leds
    for(int led = 0; led < ledsPerStrip; led++)
    {
      leds[led] *= 0.5;
    }

    // Full power on "ledPowerOn" led
    leds[ ledNumberOn ] = 1;

    // Slow down all leds
    for(int led = 0; led < ledsPerStrip; led++)
    {
        Leds.setPixel(led, (int)(255*leds[led]) << 16);
    }

    // Show Result
    Leds.show();
  
    delayMicroseconds(75000);

  }
}

