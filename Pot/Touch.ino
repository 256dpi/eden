/**
 * Touch Sensing API
 * 
 * Callbacks:
 * - touch_short()
 * - touch_long()
 */

#define TOUCH_TIME 1000
 
/* --------------------------------------------------- */ 

#include <Wire.h>
#include <Adafruit_MPR121.h>

Adafruit_MPR121 touch_ic = Adafruit_MPR121();

uint16_t touch_last = 0;
long long touch_start = 0;

void touch_setup() {  
  touch_ic.begin(0x5A);
}

void touch_loop() {
  uint16_t touch_current = touch_ic.touched();
  
  if ((touch_current & _BV(0)) && !(touch_last & _BV(0)) ) {
    touch_start = millis();
  } else if (!(touch_current & _BV(0)) && (touch_last & _BV(0)) ) {
    int diff = millis() - touch_start;
    
    if(diff < TOUCH_TIME) {
      touch_short();
    } else {
      touch_long();
    }
  }
  
  touch_last = touch_current;
}
