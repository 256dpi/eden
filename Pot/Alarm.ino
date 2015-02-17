/**
 * Alarm Subsystem
 */
 
#define A_T 400 // Interval
#define A_TT 300 // Light Interval

/* --------------------------------------------------- */

int alarm = -1;
boolean alarm_forward = false;
long long alarm_last = 0;

void alarm_loop() {
  if(alarm >= 0 && millis() - A_T > alarm_last) {
    if(alarm == 0) {
      if(alarm_forward) {
        ring_all(50, 50, 0, A_TT);
      } else {
        ring_all(100, 0, 0, A_TT);
      }
      
      alarm = 1;
    } else {
      ring_all(0, 0, 0, A_TT);
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
  ring_all(0, 0, 0, A_TT);
}

