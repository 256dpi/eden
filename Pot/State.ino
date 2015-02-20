/**
 * State System
 */
 
#define STATE_INTERVAL 3000
#define STATE_SPEED 500

/* --------------------------------------------------- */
 
int state = 0;
long long state_last_change = 0;

void state_loop(float moisture, float light) {
  if(state != 0 && millis() - STATE_INTERVAL > state_last_change) {
    if(state == 0) {
      state_wake();
    } else if(state == 1) {
      state_moisture(moisture);
    } else if(state == 2) {
      state_light(light);
    } else if(state == 3) {
      state_sleep();
    } else if(state < 0) {
      state_sleep();
    }
  }
}

void state_set(int i) {
  state = i;
  state_last_change = millis();
}

void state_wake() {
  state_set(1);
  ring_all(50, 50, 50, STATE_SPEED);
}

void state_moisture(float moisture) {
  state_set(2);
  ring_count(map(moisture, 0, 100, 0, 16), 0, 0, 50, STATE_SPEED);
}

void state_light(float light) {
  state_set(3);
  ring_count(map(light, 0, 100, 0, 16), 50, 50, 0, STATE_SPEED);
}

void state_sleep() {
  state_set(0);
  ring_all(0, 0, 0, STATE_SPEED);
}

void state_notify() {
  state_set(-1);
  ring_all(50, 0, 50, STATE_SPEED);
}

void state_alarm() {
  state_set(-2);
  ring_all(100, 0, 0, STATE_SPEED);
}

