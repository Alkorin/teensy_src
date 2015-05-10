#include <OctoWS2811.h>
#include "flake.h"

const int ledsPerStrip = 16;
const int nbFlakes = 3;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

OctoWS2811 Leds(ledsPerStrip, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

flake flakes[nbFlakes];

void setup() {
  Leds.begin();

  for(int i = 0; i < nbFlakes; i ++)
  {
    flakes[i].pos = -1;
  }
}
 
 
void loop() {
  // All black
  float leds[ledsPerStrip][3];
  memset(leds, 0, sizeof(leds));

  // Update flakes
  for(int i = 0; i < nbFlakes; i ++)
  {
    flake &f = flakes[i];
    
    // is it a dead flake ?
    if(f.pos < 0)
    {
      f.pos = 1;
      f.speed = 0.00001 + randf(0.00049);
      f.lum = 0.1; //0.5 + randf(0.5);
      makeColor(f.color, rand(), 100, 50);
    }
    
    // Update flakePos
    f.pos -= f.speed;
  
    // Draw flake in leds buffer
    drawFlake(leds, f);
  }
  
  // Update Leds
  for(int i = 0; i < ledsPerStrip; i++)
  {
    unsigned char r = leds[i][0];
    unsigned char v = leds[i][1];
    unsigned char b = leds[i][2];
    Leds.setPixel(i,  (r<<16)+(v<<8)+b);
  }

  Leds.show();
}

void drawFlake(float leds[][3], flake const& f)
{
  float pos = f.pos * ledsPerStrip;
  
  float ratio = pos - int(pos);
  float lum1 = f.lum*(1-ratio);
  float lum2 = f.lum*(ratio);
  
  for(int i = 0; i < 3; i++)
  {
    leds[int(pos)][i]   += lum1 * f.color[i];
    leds[int(pos+1)][i] += lum2 * f.color[i];
  }
}

int makeColor(unsigned char color[3], unsigned int hue, unsigned int saturation, unsigned int lightness)
{
        unsigned int red, green, blue;
        unsigned int var1, var2;

        if (hue > 359) hue = hue % 360;
        if (saturation > 100) saturation = 100;
        if (lightness > 100) lightness = 100;

        // algorithm from: http://www.easyrgb.com/index.php?X=MATH&H=19#text19
        if (saturation == 0) {
                red = green = blue = lightness * 255 / 100;
        } else {
                if (lightness < 50) {
                        var2 = lightness * (100 + saturation);
                } else {
                        var2 = ((lightness + saturation) * 100) - (saturation * lightness);
                }
                var1 = lightness * 200 - var2;
                red = h2rgb(var1, var2, (hue < 240) ? hue + 120 : hue - 240) * 255 / 600000;
                green = h2rgb(var1, var2, hue) * 255 / 600000;
                blue = h2rgb(var1, var2, (hue >= 120) ? hue - 120 : hue + 240) * 255 / 600000;
        }
        color[0] = red;
        color[1] = green;
        color[2] = blue;
}

unsigned int h2rgb(unsigned int v1, unsigned int v2, unsigned int hue)
{
        if (hue < 60) return v1 * 60 + (v2 - v1) * hue;
        if (hue < 180) return v2 * 60;
        if (hue < 240) return v1 * 60 + (v2 - v1) * (240 - hue);
        return v1 * 60;
}

float randf() {
  return (rand()/((float)RAND_MAX));
}

float randf(float n)
{
  return n * randf();
}


