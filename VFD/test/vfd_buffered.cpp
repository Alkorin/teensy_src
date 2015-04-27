#include "vfd_buffered.h"

VFD_Buffered::VFD_Buffered(uint8_t _pinEnable, uint8_t _pinRS, uint8_t _pinRW):VFD(_pinEnable, _pinRS, _pinRW)
{
  clearScreen();
  init();
  show();
}

void VFD_Buffered::clearScreen()
{
  currentOffset = 0;
  memset(buffer, ' ', sizeof(buffer));
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
  if(c == '\r')
  {
    uint8_t newOffset = (NB_CHARS * ((currentOffset / NB_CHARS)+1));
    for(; currentOffset < newOffset; currentOffset++)
    {
      buffer[currentOffset] = ' ';
    }
    currentOffset = newOffset;
  }
  else
  {
    buffer[currentOffset++] = c;
  }
  if(currentOffset == NB_LINES*NB_CHARS)
  {
    currentOffset = 0;
  }
}

void VFD_Buffered::show()
{
  VFD::setCursorAddress(0x0);
  VFD::writeData(&buffer[0], 20);
  VFD::setCursorAddress(0x40);
  VFD::writeData(&buffer[20], 20);
}
