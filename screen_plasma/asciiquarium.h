typedef struct {
  unsigned char   width;
  unsigned char   height;
  int8_t          dir;
  const char *    image;
  const uint8_t * colorMap;
} fishData;

typedef struct {
  int8_t x;
  int8_t y;
  int8_t speed;
  int8_t  subPos;
  uint8_t color;
  const   fishData * fish;
} fishElm;

typedef struct {
  char c;
  uint8_t color;
} mapStringElm;
