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

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void touch_setup() {  
  touch_ic.begin(0x5A);
}

void touch_loop() {
  currtouched = touch_ic.touched();
  
  if ((currtouched & _BV(0)) && !(lasttouched & _BV(0)) ) {
    touch_on();
  } else if (!(currtouched & _BV(0)) && (lasttouched & _BV(0)) ) {
    touch_off();
  }
  
  lasttouched = currtouched;
}
