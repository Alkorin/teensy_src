#include <SPI.h>
#include <ILI9341_t3.h>
#include "asciiquarium.h"

#define __CS 10
#define __DC 9

// global vars
ILI9341_t3 tft = ILI9341_t3(__CS, __DC);
fishElm fishes[NB_FISHES];
bubbleElm bubbles[NB_BUBBLES];
algaElm algae[NB_ALGAE];
mapStringElm mapQuariumString[SCREEN_WIDTH][SCREEN_HEIGHT];
uint8_t waterOffset[3]={0,0,0};

void setup() {
  tft.begin();
  
  asciiquarium_init();
  
  tft.setRotation(1);
  tft.setTextColor(0xFFFF,0x0000);
}

void loop(void) {
  
  //unsigned int startTime = micros();
  asciiquarium();
  //unsigned int endTime = micros();

  //tft.setCursor(0, 232);
  //tft.printf("%06d", endTime - startTime);
}

void newFish(fishElm & fish)
{
  fish.fish = fishesArray[rand()%NB_DIFF_FISHES];
  fish.speed = 1 + rand()%5;
  if(fish.fish->dir == -1)
  {
    fish.x = SCREEN_WIDTH + fish.fish->width/2 + rand()%5;
  }
  else
  {
    fish.x = 0 - fish.fish->width/2 - rand()%5;
  }
  fish.y = 4 + fish.fish->height/2 + rand()%(SCREEN_HEIGHT - 4 - fish.fish->height);
  fish.subPos = 0;
  fish.color  = rand();
}

void newBubble(fishElm const& fish)
{
  // Find an empty bubble
  for(unsigned int b = 0; b < NB_BUBBLES; b++)
  {
    if(bubbles[b].speed == 0)
    {
      // Bubble spawn on top of fish
      int posX, posY;
      if(fish.fish->dir == -1)
      {
        posX = fish.x - fish.fish->width/2;
      }
      else
      {
        posX = fish.x + fish.fish->width/2;
      }
      posY = fish.y - 1;
      if(posX >=0 && posX < SCREEN_WIDTH && posY >= 0 && posY < SCREEN_HEIGHT)
      {
        bubbles[b].x = posX;
        bubbles[b].y = posY;
        bubbles[b].startY = posY;
        bubbles[b].subPos = 0;
        bubbles[b].speed = 2;
      }
      
      break;
    }
  }
}

void newAlgae(algaElm & alga)
{
  alga.x = rand()%SCREEN_WIDTH;
  alga.height = 3+rand()%8;
}

void asciiquarium_init()
{
  for(unsigned int f = 0; f < NB_FISHES; f++)
  {
    newFish(fishes[f]);
  }
  for(unsigned int b = 0; b < NB_BUBBLES; b++)
  {
    bubbles[b].speed = 0; // 0 means no bubble
  }
  for(unsigned int a = 0; a < NB_ALGAE; a++)
  {
    newAlgae(algae[a]);
  }
}

void asciiquarium()
{
  // Elapsed time
  static unsigned int time = 0;
  time++;
  
  /*******************/
  /* Update elements */
  /*******************/

  // Update fishes
  for(unsigned int f = 0; f < NB_FISHES; f++)
  {
    fishes[f].subPos++;
    if(fishes[f].subPos == fishes[f].speed)
    {
      fishes[f].x += fishes[f].fish->dir;
      fishes[f].subPos = 0;
    }
    // If fish is now out of screen, create a new one
    if((fishes[f].fish->dir == 1 && fishes[f].x > 60) || (fishes[f].fish->dir == -1 && fishes[f].x < -8))
    {
      newFish(fishes[f]);
    }
    
    // Spawn bubbles
    if(rand() > ((RAND_MAX/100) * 95)) // 5% luck to spawn bubble
    {
      newBubble(fishes[f]);
    }
  }
  
  // Update bubbles
  for(unsigned int b = 0; b < NB_BUBBLES; b++)
  {
    bubbleElm & bubble = bubbles[b];
    if(bubble.speed)
    {
      bubble.subPos++;
      if(bubble.subPos == bubbles[b].speed)
      {
        bubble.y -= 1;
        bubble.subPos = 0;
      }
    }
  }

  /*****************/
  /* Draw elements */
  /*****************/

  // Clear mapString
  memset(mapQuariumString, 0, sizeof(mapQuariumString));
  
  // Draw water
  for(int x = 0; x < SCREEN_WIDTH; x++)
  {
    mapQuariumString[x][0].c = '~';
    mapQuariumString[x][0].color = 14;
  }
  for(int y = 0; y < 3; y++)
  {
    if(!(time%8))
    {
      // Add -1, 0, +1 each 8 frames
      waterOffset[y] += rand()%3 - 1;
    }
    for(unsigned int x = 0; x < SCREEN_WIDTH; x++)
    {
      mapQuariumString[x][y+1].c = waterMap[y][(x+waterOffset[y])%32];
      mapQuariumString[x][y+1].color = 14;
    }
  }
  
  // Draw bubbles
  for(unsigned int b = 0; b < NB_BUBBLES; b++)
  {
    bubbleElm & bubble = bubbles[b];
    if(bubble.speed)
    {
      if(mapQuariumString[bubble.x][bubble.y].c == '~' || mapQuariumString[bubble.x][bubble.y].c == '^')
      {
        // Bubble hit water level, delete it
        bubble.speed = 0;
      }
      else
      {
        int size = (3 *(bubble.startY - bubble.y)) / (bubble.startY - 3);
        mapQuariumString[bubble.x][bubble.y].c = (size == 0 ? '.' : (size == 1 ? 'o' : 'O'));
        mapQuariumString[bubble.x][bubble.y].color = 14;
      }
    }
  }
  
  // Draw algae
  for(unsigned int a = 0; a < NB_ALGAE; a++)
  {
    algaElm & alga = algae[a];
    for(unsigned int y = 0; y < alga.height; y++)
    {
      mapQuariumString[alga.x][(SCREEN_HEIGHT-1)-y].c = (y%2)?')':'(';
      mapQuariumString[alga.x][(SCREEN_HEIGHT-1)-y].color = 2;
    }
  }
  
  // Draw fishes in mapQuariumString
  for(unsigned int f = 0; f < NB_FISHES; f++)
  {
    fishElm const& fishToDraw = fishes[f];
    const char * fishImage = fishToDraw.fish->image;
    const uint8_t * fishColorMap = fishToDraw.fish->colorMap;
    int x = 0; int y = 0; char c;
    
    while((c = *fishImage++))
    {
      if(c == 'E')
      {
        x++;
      }
      else if(c == '\n')
      {
        x = 0; y++;
      }
      else
      {
        int8_t posX = fishToDraw.x - fishToDraw.fish->width/2 + x;
        int8_t posY = fishToDraw.y - fishToDraw.fish->height/2 + y;
        uint8_t color = 0;
        if(c != ' ')
        {
          color = 1+((*fishColorMap++) + fishToDraw.color)%14;
        }
        
        if(posX >=0 && posX < SCREEN_WIDTH && posY >= 0 && posY < SCREEN_HEIGHT)
        {
          mapQuariumString[posX][posY].c = c;
          mapQuariumString[posX][posY].color = color;
        }
        x++;
      } 
    }
  }
  
  /********************/
  /* Render on Screen */
  /********************/

  // Render mapQuariumString on screen
  tft.setAddrWindow(0,0,319,239);
  // For each line
  for(int mapY = 0; mapY < SCREEN_HEIGHT; mapY++)
  {
    // Line 0 to 7
    for(int subY = 0; subY < 8; subY++)
    {
      for(int x = 0; x < SCREEN_WIDTH; x++)
      {
        char c = mapQuariumString[x][mapY].c;
        for(int pixel = 0; pixel < 5; pixel++)
        {
          unsigned char fontData = font[(c*5)+pixel];
          uint16_t color = (fontData&(1<<(subY)))?colorMap[mapQuariumString[x][mapY].color]:0x0000;
          PUSH_COLOR(color);
        }
        // Black column between each chars
        PUSH_COLOR(0x00);
      }
      // Filler for end of screen (2 last column of each line)
      PUSH_COLOR(0);
      PUSH_COLOR(0);
    }
  }
}
