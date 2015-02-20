/**
 * Temperature Sensor
 *
 * Callbacks:
 * - temperature_change(float celsius)
 */

#define TEMPERATURE_PIN 1
#define TEMPERATURE_INTERVAL 3000

/* --------------------------------------------------- */

int temperature_history = 0;
long long temperature_last_read = 2000;

void temperature_loop() {
  if(millis() - TEMPERATURE_INTERVAL > temperature_last_read) {
    temperature_read();
    temperature_last_read = millis();
  }
}

void temperature_read() {
  int v = analogRead(TEMPERATURE_PIN);
  
  if(v != temperature_history) {
    temperature_change(temperature_convert(v));
    temperature_history = v;
  }
}

float temperature_convert(int value) {
  float mv = value * 5000.0 / 1024.0;
  return mv / 10.0;
}

