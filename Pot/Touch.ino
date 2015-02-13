/**
 * Touch Sensing API
 * 
 * Callbacks:
 * - touch_on(int pin)
 * - touch_off(int pin)
 */

#include <Wire.h>
#include <Adafruit_MPR121.h>

Adafruit_MPR121 touch_ic = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void touch_setup() {  
  if (!touch_ic.begin(0x5A)) {
    Serial.println("MPR121 not found!");
  }
}

void touch_loop() {
  currtouched = touch_ic.touched();
  
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      touch_on(i);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      touch_off(i);
    }
  }
  
  lasttouched = currtouched;
}
