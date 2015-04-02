/**
 * Touch Sensor
 * 
 * Callbacks:
 * - touch_short()
 * - touch_long()
 */

#define TOUCH_PIN_SEND 3
#define TOUCH_PIN_RECEIVE 4
#define TOUCH_LONG 1000
#define TOUCH_THRESHOLD 200
 
/* --------------------------------------------------- */ 

#include <CapTouch.h>

CapTouch touch = CapTouch(TOUCH_PIN_SEND, TOUCH_PIN_RECEIVE); 

long long touch_start = 0;

void touch_loop() {
  int value = touch.readTouch(15);
  
  if(value > TOUCH_THRESHOLD && touch_start == 0) {
    touch_start = millis();
  } else if(value < TOUCH_THRESHOLD && touch_start > 0) {
    int diff = millis() - touch_start;
    
    if(diff < TOUCH_LONG) {
      touch_short();
    } else {
      touch_long();
    }
    
    touch_start = 0;
  } else if(millis() - TOUCH_LONG > touch_start && touch_start > 0) {
    touch_long();
    touch_start = 0;
  }
}

