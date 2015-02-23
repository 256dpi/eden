/**
 * Moisture Sensor
 *
 * Callbacks:
 * - moisture_change(float percent)
 */

#define MOISTURE_PIN 0
#define MOISTURE_INTERVAL 3000
#define MOISTURE_MIN 550
#define MOISTURE_MAX 750

/* --------------------------------------------------- */

int moisture_history = 0;
long long moisture_last_read = 1000;

void moisture_loop() {
  if(millis() - MOISTURE_INTERVAL > moisture_last_read) {
    moisture_read();
    moisture_last_read = millis();
  }
}

void moisture_read() {
  int v = analogRead(MOISTURE_PIN);
  
  if(v != moisture_history) {
    int vv = map(v, MOISTURE_MIN, MOISTURE_MAX, 0, 100);
    vv = constrain(vv, 0, 100);
    
    moisture_change(vv);
    moisture_history = v;
  }
}

