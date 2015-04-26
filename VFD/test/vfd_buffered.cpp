#include "vfd_buffered.h"

VFD_Buffered::VFD_Buffered(uint8_t _pinEnable, uint8_t _pinRS, uint8_t _pinRW):VFD(_pinEnable, _pinRS, _pinRW)
{
  currentOffset = 0;
  memset(buffer, '*', sizeof(buffer));

  VFD::init();
}

void VFD_Buffered::writeString(const char * s)
{
  char c;
  while((c = *s++))
  {
    writeChar(c);
  }
}

void VFD_Buffered::writeChar(char c)
{
  buffer[currentOffset++] = c;
  if(currentOffset == NB_LINES*NB_CHARS)
  {
    currentOffset = 0;
  }
}

void VFD_Buffered::show()
{
  cursorHome();
  VFD::writeData(&buffer[0], 20);

  currentOffset = 0;
}
