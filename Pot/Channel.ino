/**
 * Channel Selector
 *
 * Callbacks:
 * - channel_selected(number)
 */

#define CHANNEL_PIN 3
#define CHANNEL_MIN 0
#define CHANNEL_MAX 950
#define CHANNEL_WAIT 1000

/* --------------------------------------------------- */

int channel_history = 0;
long long channel_last_change = 0;

void channel_loop() {
  channel_read();
  
  if(channel_last_change > 0 && millis() - CHANNEL_WAIT > channel_last_change) {
    channel_selected(channel_history);
    channel_last_change = 0;
    ring_all(0, 0, 0, 500);
  }
}

void channel_read() {
  int v = constrain(map(analogRead(CHANNEL_PIN), CHANNEL_MIN, CHANNEL_MAX, 1, 16), 1, 16);
  
  if(v != channel_history) {
    channel_history = v;
    channel_last_change = millis();
    ring_count(v, 50, 50, 50, 300);
  }
}

