#ifndef __VFD_BUFFERED_H__
#define __VFD_BUFFERED_H__

#define NB_LINES 2
#define NB_CHARS 20

#include "vfd.h"

class VFD_Buffered : private VFD {
  public:
    VFD_Buffered(uint8_t _pinEnable, uint8_t _pinRS, uint8_t _pinRW);
    
    void writeString(const char * s);
    void writeChar(char c);
    void clearScreen();
    void setPos(uint8_t line, uint8_t pos) { currentOffset = line * NB_CHARS + pos; }

    // Update VFD
    void show();

  private:
    char buffer[NB_LINES*NB_CHARS];
    uint8_t currentOffset;
};

#endif

