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
    void clearScreen() { sendCommand(0x01); delayMicroseconds(100); }

    // Cursor Home -- 666ns
    void cursorHome() { sendCommand(0x02); }

    // EntryModeSet -- 666ns

    // DisplayOnOff --- 666ns
    void displayOn(CURSOR_MODE c, BLINK_MODE b) { sendCommand(0x0C | c | b); }
    void displayOff() { sendCommand(0x08); }
    
    // Cursor Display Shift -- 666ns

    // Function Set -- 666ns
    void setMode(CPU_INTERFACE_MODE i) { sendCommand(0x30 | i); }
    
    // Brightness control -- 666ns (need to send FunctionSet before)
    
    // Set CG RAM Address -- 666 ns
    
    // Set DD Ram Address -- 666 ns
    void setCursorAddress(uint8_t a) { sendCommand(0x80 | a); }


    /* Helpers */
    void writeChar(char c) { sendData(c); }
    void writeData(const char * d, size_t len);
    void writeString(const char * s);




  private:
    void sendCommand(uint8_t c);
    void sendData(uint8_t d);
  
    uint8_t pinEnable;
    uint8_t pinRS;
    uint8_t pinRW;
};

#endif
