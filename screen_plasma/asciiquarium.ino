#ifdef ASCIIQUARIUM

extern const unsigned char font[];

fishElm fishes[5];

#define NB_FISHES       (sizeof(fishes)/sizeof(fishElm))
#define NB_DIFF_FISHES  (sizeof(fishesArray)/sizeof(fishData *))

mapStringElm mapQuariumString[53][30];

void FASTRUN newFish(fishElm & fish)
{
    fish.fish = fishesArray[rand()%NB_DIFF_FISHES];
    fish.speed = 1 + rand()%5;
    if(fish.fish->dir == -1)
    {
      fish.x = 53 + fish.fish->width/2 + rand()%5;
    }
    else
    {
      fish.x = 0 - fish.fish->width/2 - rand()%5;
    }
    fish.y = 4 + fish.fish->height/2 + rand()%(30 - 4 - fish.fish->height);
    fish.subPos = 0;
}

void asciiquarium_init()
{
  for(unsigned int f = 0; f < NB_FISHES; f++)
  {
    newFish(fishes[f]);
  }
}

void FASTRUN asciiquarium()
{
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
  }
  
  // Clear mapString
  memset(mapQuariumString, 0, sizeof(mapQuariumString));
  
  // Draw water
  for(int y = 0; y < 4; y++)
  {
    for(int x = 0; x < 53; x++)
    {
      mapQuariumString[x][y].c = waterMap[y][x];
      mapQuariumString[x][y].color = 0x07FF;
    }
  }  
  // Draw fishes
  for(unsigned int f = 0; f < NB_FISHES; f++)
  {
    fishElm const& fishToDraw = fishes[f];
    const char * fishImage = fishToDraw.fish->image;
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
        if(posX >=0 && posX < 53 && posY >= 0 && posY < 30)
        {
          mapQuariumString[posX][posY].c = c;
          mapQuariumString[posX][posY].color = 0xFFFF;
        }
        x++;
      } 
    }
  }
  
  // Draw on screen
  tft.setAddrWindow(0,0,319,239);
  // For each line
  for(int mapY = 0; mapY < 30; mapY++)
  {
    // Line 1 to 7
    for(int subY = 0; subY < 8; subY++)
    {
      for(int x = 0; x < 53; x++)
      {
        char c = mapQuariumString[x][mapY].c;
        for(int pixel = 0; pixel < 5; pixel++)
        {
          unsigned char fontData = font[(c*5)+pixel];
          uint16_t color = (fontData&(1<<(subY)))?mapQuariumString[x][mapY].color:0x0000;
          
          while (((SPI0.SR) & (15 << 12)) > (3 << 12)) ;
          SPI0_PUSHR = (color) | (0x00010000) | SPI_PUSHR_CTAS(1);
        }
        while (((SPI0.SR) & (15 << 12)) > (3 << 12)) ;
        SPI0_PUSHR = (0) | (0x00010000) | SPI_PUSHR_CTAS(1);
      }
      // Filler for end of screen
      for(int pixel = 0; pixel < 2; pixel++)
      {
        while (((SPI0.SR) & (15 << 12)) > (3 << 12)) ;
        SPI0_PUSHR = (0) | (0x00010000) | SPI_PUSHR_CTAS(1);
      }
    }
  }
}

#endif
