typedef struct {
  unsigned char width;
  unsigned char height;
  int8_t        dir;
  const char *  image;
} fishData;

typedef struct {
  int16_t x;
  int16_t y;
  int16_t speed;
  int8_t  subPos;
  uint8_t color;
  const   fishData * fish;
} fishElm;

typedef struct {
  char c;
  uint8_t color;
} mapStringElm;
