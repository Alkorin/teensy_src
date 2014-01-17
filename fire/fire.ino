#include <OctoWS2811.h>

const int ledsPerStrip = 16;
const int durationBetweenChanges = 200.0f; // 1s

const int FR = 0xFF * 0.2;
const int FG = 0x9F * 0.2;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

OctoWS2811 Leds(ledsPerStrip, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

float lastFirePos = 0;
float firePos = 0;
float wantedFirePos = 0;
int timeLastChange = millis();

float randf()
{
    return (rand() / (float)RAND_MAX);
}

void setup() {
  Leds.begin();
}

void loop() {
    int elapsedTimeSinceChange = millis() - timeLastChange;

    // Update current firePos state
    if(elapsedTimeSinceChange >= durationBetweenChanges)
    {
      // New direction
      lastFirePos = firePos;
      timeLastChange = millis();
      wantedFirePos = (ledsPerStrip-1) * randf();
    }
    else
    {
      // Animation
      firePos = lastFirePos + (((wantedFirePos-lastFirePos) * elapsedTimeSinceChange) / durationBetweenChanges);
    }
        
    // Update leds
    {
      // All black
      memset(drawingMemory, 0, sizeof(drawingMemory));
    
      // Before firePos
      for(int i = 0; i < firePos; i++)
      {
        int G = FG * ((firePos-i) / firePos);
        Leds.setPixel(i, (int)((FR << 16) + (G << 8)));
      }
    
      // firePos pixel
      if(firePos < (ledsPerStrip - 1))
      {
        float lum = firePos - int(firePos);
        int R = FR * lum;
        Leds.setPixel(firePos+1, (int)((R << 16)));
      }
    
      // Show Result
      Leds.show();
    }
}

    /*{
      char buff[80];
      sprintf(buff, "firePos=%f - last=%f, new=%f, currTime=%d, timeLast=%d\r\n", firePos, lastFirePos, wantedFirePos, millis(), timeLastChange);
      Serial.write(buff);
    }*/
