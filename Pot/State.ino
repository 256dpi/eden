/**
 * State Subsystem
 */

void state_wake() {
  ring_all(50, 50, 50, 500);
}

void state_sleep() {
  ring_all(0, 0, 0, 500);
}

