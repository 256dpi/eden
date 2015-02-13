/**
 * Moisture Sensor API
 *
 * Callbacks:
 * - moisture_read(int value);
 */

#define M_R1 6 // Rod 1 Pin
#define M_R2 7 // Rod 2 Pin
#define M_IN 0 // Read Pin
#define M_T 2000 // Read Interval (ms)

long long moisture_last_action = 0;
int moisture_state = 0;
int moisture_read_1 = 0;
int moisture_read_2 = 0;

void moisture_setup() {
  pinMode(M_R1, OUTPUT);
  pinMode(M_R2, OUTPUT);
}

void moisture_loop() {
  if(millis() - (M_T / 3) > moisture_last_action) {
    if(moisture_state == 0) {
      moisture_flip(true);
      moisture_state++;
    } else if(moisture_state == 1) {
      moisture_read_1 = analogRead(M_IN);
      moisture_flip(false);
      moisture_state++;
    } else {
      moisture_read_2 = 1023 - analogRead(M_IN);
      moisture_read((moisture_read_1 + moisture_read_2) / 2);
      moisture_state = 0;
    }
    
    moisture_last_action = millis();
  }
}

void moisture_flip(boolean flip){
  if(flip){
    digitalWrite(M_R1, HIGH);
    digitalWrite(M_R2, LOW);
  }else{
    digitalWrite(M_R1, LOW);
    digitalWrite(M_R2, HIGH);
  }
}

