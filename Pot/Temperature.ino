/**
 * Temperature API
 *
 * Callbacks:
 * - temperature_change(float temp)
 */

#define T_PIN 2
#define T_T 2000

int temperature_history = 0;
long long temperature_last_read = 0;

void temperature_loop() {
  if(millis() - T_T > temperature_last_read) {
    temperature_read();
    temperature_last_read = millis();
  }
}

void temperature_read() {
  int temp = analogRead(T_PIN);
  
  if(temp != temperature_history) {
    temperature_change(temperature_convert(temp));
    temperature_history = temp;
  }
}

float temperature_convert(int value) {
  float mv = value * 5000.0 / 1024.0;
  return mv / 10.0;
}

