/**
 * Temperature Sensor
 *
 * Callbacks:
 * - temperature_change(float celsius)
 */

#define TEMPERATURE_PIN 1
#define TEMPERATURE_READINGS 10
#define TEMPERATURE_INTERVAL 2000

/* --------------------------------------------------- */

int temperature_history[TEMPERATURE_READINGS];
int temperature_step = 0;

long long temperature_last_step = 0;

void temperature_loop() {
  if(millis() - TEMPERATURE_INTERVAL / TEMPERATURE_READINGS > temperature_last_step) {
    if(temperature_step < TEMPERATURE_READINGS) {
      temperature_history[temperature_step] = analogRead(TEMPERATURE_PIN);
      temperature_step++; 
    } else {
      temperature_calculate();
      temperature_step = 0;
    }
    
    temperature_last_step = millis();
  }
}

void temperature_calculate() {
  int total = 0;
  
  for(int i=0; i < TEMPERATURE_READINGS; i++) { 
    total += temperature_history[i];
  }
  
  temperature_change(temperature_convert(total / TEMPERATURE_READINGS));
}

float temperature_convert(int value) {
  float mv = value * 5000.0 / 1024.0;
  return mv / 10.0;
}

