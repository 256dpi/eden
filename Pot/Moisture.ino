/**
 * Moisture Sensor
 *
 * Callbacks:
 * - moisture_change(float percent)
 */

#define MOISTURE_PIN 0
#define MOISTURE_INTERVAL 2000

/* --------------------------------------------------- */

int moisture_history = 0;
long long moisture_last_read = 0;

void moisture_loop() {
  if(millis() - MOISTURE_INTERVAL > moisture_last_read) {
    moisture_read();
    moisture_last_read = millis();
  }
}

void moisture_read() {
  int v = analogRead(MOISTURE_PIN);
  
  if(v != moisture_history) {
    moisture_change(v / 1023.0 * 100.0);
    moisture_history = v;
  }
}

