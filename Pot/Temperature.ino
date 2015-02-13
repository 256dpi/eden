/**
 * Temperature API
 *
 * Callbacks:
 * - temperature_change(float celsius)
 */

#define T_PIN 1 // Pin of LM35 reading
#define T_R 10 // Number of readings
#define T_T 2000 // Reading interval

int temperature_history[T_R];
int temperature_step = 0;

long long temperature_last_step = 0;

void temperature_loop() {
  if(millis() - T_T/T_R > temperature_last_step) {
    if(temperature_step < T_R) {
      temperature_history[temperature_step] = analogRead(T_PIN);
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
  
  for(int i=0; i < T_R; i++) { 
    total += temperature_history[i];
  }
  
  temperature_change(temperature_convert(total / T_R));
}

float temperature_convert(int value) {
  float mv = value * 5000.0 / 1024.0;
  return mv / 10.0;
}

