#ifndef _ASCIIQUARIUM_H_
#define _ASCIIQUARIUM_H_

#include "Arduino.h"
#include "asciiquarium_data.h"

#define SCREEN_WIDTH  53
#define SCREEN_HEIGHT 30

#define NB_FISHES 5
#define NB_BUBBLES 10
#define NB_ALGAE 15

extern const unsigned char font[];

typedef struct {
  int8_t  x;
  int8_t  y;
  int8_t  speed;
  int8_t  subPos;
  uint8_t z;
  uint8_t color;
  const   fishData * fish;
} fishElm;

typedef struct {
  int8_t  x;
  int8_t  y;
  int8_t  startY;
  uint8_t z;
  int8_t  speed;
  int8_t  subPos;
} bubbleElm;

typedef struct {
  int8_t x;
  uint8_t height;
  uint8_t z;
  int8_t dir;
} algaElm;

typedef struct {
  uint8_t z;
  char c;
  uint8_t color;
} mapStringElm;

#define PUSH_COLOR(x)         while (((SPI0_SR) & (15 << 12)) > (3 << 12));         \
                              SPI0_PUSHR = (x) | (0x00010000) | SPI_PUSHR_CTAS(1);

#endif
