/**
 * Alarm System
 *
 * Callbacks
 * - alarm_trigger()
 */
 
#define ALARM_MOISTURE_MIN 25
#define ALARM_INTERVAL 3000

/* --------------------------------------------------- */

long long alarm_last_trigger = 0;

void alarm_loop(float moisture) {
  if(millis() - ALARM_INTERVAL > alarm_last_trigger) {
    alarm_last_trigger = 0;
  }
  
  if(moisture < ALARM_MOISTURE_MIN && alarm_last_trigger == 0) {
    alarm_trigger();
    alarm_last_trigger = millis();
  }
}

