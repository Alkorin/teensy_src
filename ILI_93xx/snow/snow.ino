#include <SPI.h>
#include <ILI9341_t3.h>
#include "snow.h"

#define __CS 10
#define __DC 9

#define DEBUG_FPS

// global vars
ILI9341_t3 tft = ILI9341_t3(__CS, __DC);

snowflakeElm snowflakes[NB_SNOWFLAKES];
uint8_t      snowLevel[320];

pixelElm frameBuffer[240][160];

const uint16_t colorMap[] = {
  0x0000,  // Black
  0xc800,  // Red
  0x0660,  // Green
  0xce60,  // Yellow
  0x0019,  // Blue
  0xc819,  // Magenta
  0x0679,  // Cyan
  0xe73c,  // Gray
  0x7bef,  // Dark Gray
  0xf800,  // Red
  0x07e0,  // Green
  0xffe0,  // Yellow
  0x5aff,  // Blue
  0xf81f,  // Magenta
  0x07ff,  // Cyan
  0xffff,  // White
};

void setup() {
  tft.begin();
  
  snow_init();
  
  tft.setRotation(1);
  tft.setTextColor(0xFFFF,0x0000);
}

void loop(void) {
#ifdef DEBUG_FPS
  unsigned int startTime = micros();
#endif

  snow();

#ifdef DEBUG_FPS
  unsigned int endTime = micros();

  tft.setCursor(0, 232);
  tft.printf("%06d", endTime - startTime);
#endif
}

void newSnowflake(snowflakeElm & snowflake, boolean isInit = false)
{
  snowflake.y      = isInit ? (rand()%240) : 0;
  snowflake.x      = rand() % 320;
  snowflake.speed  = 1+rand()%2;
  snowflake.subPos = 0;
}

void updateFrameBuffer(int x, int y, uint8_t color)
{
  if(y < 240)
  {
    if(x % 2)
    {
      frameBuffer[y][x/2].color2 = color;
    }
    else
    {
      frameBuffer[y][x/2].color1 = color;
    }
  }
}

void snow_init()
{
  for(int s = 0; s < NB_SNOWFLAKES; s++)
  {
    newSnowflake(snowflakes[s], true);
  }
  for(int i = 0; i < 320; i++)
  {
    snowLevel[i] = 239;
  }
}

void snow()
{
  // Elapsed time
  static unsigned int time = 0;
  time++;
  
  /*******************/
  /* Update elements */
  /*******************/
  for(int s = 0; s < NB_SNOWFLAKES; s++)
  {
    snowflakeElm & snowflake = snowflakes[s];
    
    snowflake.y++;
    if(snowflake.y >= snowLevel[snowflake.x])
    {
      snowLevel[snowflake.x]--;
      newSnowflake(snowflake);
    }
  }
  
  /*****************/
  /* Draw elements */
  /*****************/
  memset(frameBuffer, 0, sizeof(frameBuffer));
  
  for(int s = 0; s < NB_SNOWFLAKES; s++)
  {
    updateFrameBuffer(snowflakes[s].x, snowflakes[s].y, 0x0F);
  }

  /********************/
  /* Render on Screen */
  /********************/

  // Render mapQuariumString on screen
  tft.setAddrWindow(0,0,319,239);

  for(int y = 0; y < 240; y++)
  {
    for(int x = 0; x < 160; x++)
    {
      if(y <= snowLevel[2*x])
      {
        PUSH_COLOR(colorMap[frameBuffer[y][x].color1]);
      }
      else
      {
        PUSH_COLOR(colorMap[15]);
      }
      if(y <= snowLevel[2*x+1])
      {
        PUSH_COLOR(colorMap[frameBuffer[y][x].color2]);
      }
      else
      {
        PUSH_COLOR(colorMap[15]);
      }      
    }
  }
}
