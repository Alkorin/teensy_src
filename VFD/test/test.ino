#include "Arduino.h"
#include "vfd.h"

VFD vfd(0, 1, 3);

void setup() {
  vfd.init();
}

void loop(void) {
  static int i = 0;
  i++;
  
  char buff[21];
  sniprintf(buff, 20, "%d \x1a", i);
  
  vfd.cursorHome();
  vfd.writeString(buff);
}
