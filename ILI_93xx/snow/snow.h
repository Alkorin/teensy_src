#ifndef __SNOW_H__
#define __SNOW_H__

#define NB_SNOWFLAKES 100

typedef struct {
  uint16_t x;
  uint8_t  y;
  int8_t  speed;
  int8_t  subPos;
} snowflakeElm;

typedef struct {
  uint8_t color1 : 4;
  uint8_t color2 : 4;
} pixelElm;

#define PUSH_COLOR(x)         while (((SPI0_SR) & (15 << 12)) > (3 << 12));         \
                              SPI0_PUSHR = (x) | (0x00010000) | SPI_PUSHR_CTAS(1);
#endif
