#ifndef _ASCIIQUARIUM_DATA_H_
#define _ASCIIQUARIUM_DATA_H_

#include "Arduino.h"

#define NB_DIFF_FISHES 16

typedef struct {
  unsigned char   width;
  unsigned char   height;
  int8_t          dir;
  const char *    image;
  const uint8_t * colorMap;
} fishData;

extern const fishData * fishesArray[NB_DIFF_FISHES];
extern const char * waterMap[];
extern const uint16_t colorMap[];

#endif
