#include "Arduino.h"
#include "vfd_buffered.h"

VFD_Buffered vfd(0, 1, 3);

void setup() {
}

void loop(void) {
  while(Serial.available())
  {
    vfd.writeChar(Serial.read());
  }
  vfd.show();
}
