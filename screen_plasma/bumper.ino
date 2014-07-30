#ifdef BUMPER

int16_t rainbowColors[180];

void bumperSetup()
{
  for (int i=0; i<180; i++) {
    int hue = i*2;
    int saturation = 100;
    int lightness = 50;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, lightness);
  }
}

void FASTRUN bumper()
{
  static unsigned int time = 1;
  time++;
  
  tft.setAddrWindow(0,0,239,319);

  int deltaX = fastCosineCalc(time)/2;
  int deltaY = fastCosineCalc(time+128);

  for(int x = -160; x < 160; x++)
  {
    for(int y = -120; y < 120; y++)
    {
      int index = time + ((x-deltaX)*(x-deltaX) + (y-deltaY)*(y-deltaY))/32;

      unsigned int color = rainbowColors[index%180];

      while (((SPI0.SR) & (15 << 12)) > (3 << 12)) ;
      SPI0_PUSHR = (color) | (0x00010000) | SPI_PUSHR_CTAS(1);
    }
  }
}
#endif
