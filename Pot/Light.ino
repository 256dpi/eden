/**
 * Light API
 *
 * Callbacks:
 * - light_change(float percent)
 */

#define T_PIN 4
#define T_T 2000

int light_history = 0;
long long light_last_read = 0;

void light_loop() {
  if(millis() - T_T > light_last_read) {
    light_read();
    light_last_read = millis();
  }
}

void light_read() {
  int temp = analogRead(T_PIN);
  
  if(temp != light_history) {
    light_change(temp / 1023.0 * 100.0);
    light_history = temp;
  }
}

