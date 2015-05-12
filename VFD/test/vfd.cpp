#include "vfd.h"

VFD::VFD(uint8_t _pinEnable, uint8_t _pinRS, uint8_t _pinRW):pinEnable(_pinEnable), pinRS(_pinRS), pinRW(_pinRW)
{
}

void VFD::init()
{
  // Wait 100ms to let VFD's µC to initialize
  delayMicroseconds(100000); // 100ms

  // Set PORTD as output
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(5, OUTPUT);
  
  // Set control pins as output
  pinMode(pinEnable, OUTPUT);
  pinMode(pinRS, OUTPUT);
  pinMode(pinRW, OUTPUT);
  
  // Set enable to low
  digitalWriteFast(pinEnable, 0);
  
  setMode(BITS_8);
  displayOn(CURSOR_OFF, BLINK_OFF);
  clearScreen();
}

void VFD::sendCommand(uint8_t c)
{
  digitalWriteFast(pinRS, 0);
  digitalWriteFast(pinRW, 0);

  GPIOD_PDOR = c;
  digitalWriteFast(pinEnable, 1);
  digitalWriteFast(pinEnable, 0);
}

void VFD::sendData(uint8_t c)
{
  digitalWriteFast(pinRS, 1);
  digitalWriteFast(pinRW, 0);

  GPIOD_PDOR = c;
  digitalWriteFast(pinEnable, 1);
  digitalWriteFast(pinEnable, 0);
}

void VFD::writeString(const char * s)
{
  char c;
  digitalWriteFast(pinRS, 1);
  digitalWriteFast(pinRW, 0);
  while((c = *s++))
  {
      GPIOD_PDOR = c;
      digitalWriteFast(pinEnable, 1);
      digitalWriteFast(pinEnable, 0);  
  }
}

void VFD::writeData(const char * s, size_t len)
{
  digitalWriteFast(pinRS, 1);
  digitalWriteFast(pinRW, 0);
  while(len--)
  {
      GPIOD_PDOR = *s++;
      digitalWriteFast(pinEnable, 1);
      digitalWriteFast(pinEnable, 0);  
  }
}
