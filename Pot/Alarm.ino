/**
 * Alarm System
 */
 
#define ALARM_SPEED 400
#define ALARM_SPEED2 300

/* --------------------------------------------------- */

int alarm = -1;
boolean alarm_forward = false;
long long alarm_last = 0;

void alarm_loop() {
  if(alarm >= 0 && millis() - ALARM_SPEED > alarm_last) {
    if(alarm == 0) {
      if(alarm_forward) {
        ring_all(50, 50, 0, ALARM_SPEED2);
      } else {
        ring_all(100, 0, 0, ALARM_SPEED2);
      }
      
      alarm = 1;
    } else {
      ring_all(0, 0, 0, ALARM_SPEED2);
      alarm = 0;
    }
      
    alarm_last = millis();
  } 
}

void alarm_on(boolean fwd) {
  alarm = 0;
  alarm_forward = fwd;
}

void alarm_off() {
  alarm = -1;
  ring_all(0, 0, 0, ALARM_SPEED2);
}

