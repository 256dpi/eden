/**
 * Touch Sensing API
 * 
 * Callbacks:
 * - touch_on()
 * - touch_off()
 */

#include <Wire.h>
#include <Adafruit_MPR121.h>

Adafruit_MPR121 touch_ic = Adafruit_MPR121();

uint16_t touch_last = 0;

void touch_setup() {  
  touch_ic.begin(0x5A);
}

void touch_loop() {
  uint16_t touch_current = touch_ic.touched();
  
  if ((touch_current & _BV(0)) && !(touch_last & _BV(0)) ) {
    touch_on();
  } else if (!(touch_current & _BV(0)) && (touch_last & _BV(0)) ) {
    touch_off();
  }
  
  touch_last = touch_current;
}
