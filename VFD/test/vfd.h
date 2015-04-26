#ifndef __VFD_H__
#define __VFD_H__

#include "Arduino.h"

#define NB_LINES 2
#define NB_CHARS 20

enum CPU_INTERFACE_MODE { BITS_4 = 0 , BITS_8 = 0x10 };
enum CURSOR_MODE { CURSOR_OFF = 0, CURSOR_ON = 0x02};
enum BLINK_MODE { BLINK_OFF = 0, BLINK_ON = 0x01};

/* Uses PORTD (pins (5, 21, 20, 6, 8, 7, 14, 2)) for DATA */
class VFD {
  public:
    VFD(uint8_t _pinEnable, uint8_t _pinRS, uint8_t _pinRW);
    void init();
    
    /* Instructions of CU20029 */
    // Display Clear -- 100µS
    void clearScreen() { writeCommand(0x01); delayMicroseconds(99); }

    // Cursor Home -- 666ns
    void cursorHome() { writeCommand(0x02); }

    // EntryModeSet -- 666ns

    // DisplayOnOff --- 666ns
    void displayOn(CURSOR_MODE c, BLINK_MODE b) { writeCommand(0x0C | c | b); }
    void displayOff() { writeCommand(0x08); }
    
    // Cursor Display Shift -- 666ns

    // Function Set -- 666ns
    void setMode(CPU_INTERFACE_MODE i) { writeCommand(0x30 | i); }
    
    // Brightness control -- 666ns (need to send FunctionSet before)


    /* Helpers */
    void writeChar(char c) { writeData(c); }
    void writeData(const char * d, size_t len);
    void writeString(const char * s);




  private:
    void writeCommand(uint8_t c);
    void writeData(uint8_t d);
  
    uint8_t pinEnable;
    uint8_t pinRS;
    uint8_t pinRW;
};

#endif
