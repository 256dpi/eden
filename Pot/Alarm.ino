/**
 * Alarm Subsystem
 */
 
#define A_T 400 // Interval
#define A_TT 300 // Light Interval

/* --------------------------------------------------- */

int alarm = -1;
long long alarm_last = 0;

void alarm_loop() {
  if(alarm >= 0 && millis() - A_T > alarm_last) {
    if(alarm == 0) {
      ring_all(255, 0, 0, A_TT);
      alarm = 1;
    } else {
      ring_all(0, 0, 0, A_TT);
      alarm = 0;
    }
      
    alarm_last = millis();
  } 
}

void alarm_on() {
  alarm = 0;
}

void alarm_off() {
  alarm = -1;
  ring_all(0, 0, 0, A_TT);
}

