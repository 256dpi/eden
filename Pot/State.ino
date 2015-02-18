/**
 * State System
 */

void state_wake() {
  ring_all(50, 50, 50, 500);
}

void state_moisture(int count) {
  ring_count(count, 0, 0, 50, 500);
}

void state_light(int count) {
  ring_count(count, 50, 50, 0, 500);
}

void state_sleep() {
  ring_all(0, 0, 0, 500);
}

