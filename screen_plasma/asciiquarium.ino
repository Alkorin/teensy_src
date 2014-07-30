#ifdef ASCIIQUARIUM

extern const unsigned char font[];

const char fish1Img[] = {
  0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x5c,0x0a,0x45,0x45,0x45,0x45,0x45,0x2e,0x2e,0x2e,0x5c,0x2e,0x2e,0x2c,0x0a,0x5c,0x45,0x45,0x2f,0x27,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x5c,0x0a,0x45,0x3e,0x3d,0x20,0x20,0x20,0x20,0x20,0x28,0x20,0x20,0x27,0x20,0x3e,0x0a,0x2f,0x45,0x45,0x5c,0x20,0x20,0x20,0x20,0x20,0x20,0x2f,0x20,0x2f,0x0a,0x45,0x45,0x45,0x45,0x60,0x22,0x27,0x22,0x27,0x2f,0x27,0x27,0x00
};
const fishData f1 = {
  .width = 14,
  .height = 6,
  .dir = 1,
  .image = fish1Img,
};

const char fish2Img[] = {
  0x45,0x45,0x45,0x45,0x45,0x45,0x2f,0x0a,0x45,0x45,0x2c,0x2e,0x2e,0x2f,0x2e,0x2e,0x2e,0x0a,0x45,0x2f,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x27,0x5c,0x45,0x45,0x2f,0x0a,0x3c,0x20,0x27,0x20,0x20,0x29,0x20,0x20,0x20,0x20,0x20,0x3d,0x3c,0x0a,0x45,0x5c,0x20,0x5c,0x20,0x20,0x20,0x20,0x20,0x20,0x2f,0x45,0x45,0x5c,0x0a,0x45,0x45,0x60,0x27,0x5c,0x27,0x22,0x27,0x22,0x27,0x00
};
const fishData f2 = {
  .width = 14,
  .height = 6,
  .dir = -1,
  .image = fish2Img,
};

const char fish3Img[] = {
  0x45,0x45,0x45,0x45,0x5c,0x0a,0x5c,0x45,0x2f,0x2d,0x2d,0x5c,0x0a,0x3e,0x3d,0x20,0x20,0x28,0x6f,0x3e,0x0a,0x2f,0x45,0x5c,0x5f,0x5f,0x2f,0x0a,0x45,0x45,0x45,0x45,0x2f,0x0a,0x00
};
const fishData f3 = {
  .width = 7,
  .height = 5,
  .dir = 1,
  .image = fish3Img,
};

const char fish4Img[] = {
  0x45,0x45,0x2f,0x0a,0x45,0x2f,0x2d,0x2d,0x5c,0x45,0x2f,0x0a,0x3c,0x6f,0x29,0x20,0x20,0x3d,0x3c,0x0a,0x45,0x5c,0x5f,0x5f,0x2f,0x45,0x5c,0x0a,0x45,0x45,0x5c,0x0a,0x00
};
const fishData f4 = {
  .width = 7,
  .height = 5,
  .dir = -1,
  .image = fish4Img,
};

const char fish5Img[] = {
  0x45,0x45,0x5f,0x5f,0x0a,0x3e,0x3c,0x5f,0x27,0x3e,0x0a,0x45,0x45,0x45,0x27,0x0a,0x00
};
const fishData f5 = {
  .width = 5,
  .height = 3,
  .dir = 1,
  .image = fish5Img,
};

const char fish6Img[] = {
  0x45,0x5f,0x5f,0x0a,0x3c,0x27,0x5f,0x3e,0x3c,0x0a,0x45,0x60,0x0a,0x00
};
const fishData f6 = {
  .width = 5,
  .height = 3,
  .dir = -1,
  .image = fish6Img,
};

const fishData * fishesArray[] = { &f1, &f2, &f3, &f4, &f5, &f6 };

const char * waterMap[] = {
  "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
  "^^^^ ^^^  ^^^   ^^^    ^^^^      ^^^^ ^^^  ^^^   ^^^ ",
  "^^^^      ^^^^     ^^^    ^^     ^^^^      ^^^^     ^",
  "^^      ^^^^      ^^^    ^^^^^^  ^^      ^^^^      ^^",
};

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
