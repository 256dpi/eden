/**
 * Pot - Pot Controller
 *
 * Eden Project: A networked pot.
 */

#define ID "pot1"
#define KEY "5938e5400448b62b"
#define SECRET "e53d9b341079b265ec2ea7a3da6a6fe0"

/* --------------------------------------------------- */

#include <Bridge.h>
#include <YunMQTTClient.h>

const char * pot_id = ID;
const char * pot_key = KEY;
const char * pot_secret = SECRET;

boolean pot_online = false;
boolean pot_booted = false;

float pot_temperature = 24.0;
float pot_light = 50.0;
float pot_moisture = 50.0;

char pot_topic_buffer[32];

YunMQTTClient client("connect.shiftr.io", 1883);

void setup() {
  Bridge.begin();
  Serial.begin(9600);

  ring_setup();

  if (client.connect(pot_id, pot_key, pot_secret)) {
    client.subscribe("+/touch/long");
    client.subscribe("+/alarm");

    pot_online = true;
    ring_all(0, 255, 0, 1000);
  } else {
    ring_all(255, 0, 0, 1000);
  }
}

void loop() {
  if (pot_online) {
    client.loop();
    moisture_loop();
    ring_loop();
    touch_loop();
    temperature_loop();
    light_loop();
    alarm_loop(pot_moisture);
    state_loop(pot_moisture, pot_light, pot_temperature);

    if (!pot_booted && millis() > 5000) {
      ring_all(0, 0, 0, 500);
      pot_booted = true;
    }
  }
}

const char * make_topic(const char * string) {
  int id_len = strlen(pot_id);
  strcpy(pot_topic_buffer, pot_id);
  pot_topic_buffer[id_len] = '/';
  strcpy(pot_topic_buffer + id_len + 1, string);
  return pot_topic_buffer;
}

/* MQTTClient */

void messageReceived(String topic, String payload, char * bytes, unsigned int len) {
  if (topic.indexOf("touch/long") != -1 && payload.indexOf(pot_id) == -1) {
    state_wake();
  } else if (topic.indexOf("alarm") != -1 && payload.indexOf(pot_id) == -1) {
    state_notify();
  }
}

/* Moisture */

void moisture_change(float value) {
  pot_moisture = value;
  client.publish(make_topic("data/moisture.n"), String(value));
}

/* Touch */

void touch_short() {
  client.publish(make_topic("touch/short"), pot_id);
  state_wake();
}

void touch_long() {
  client.publish(make_topic("touch/long"), pot_id);
  state_wake();
}

/* Temperature */

void temperature_change(float value) {
  pot_temperature = value;
  client.publish(make_topic("data/temperature.n"), String(value));
}

/* Light */

void light_change(float value) {
  pot_light = value;
  client.publish(make_topic("data/light.n"), String(value));
}

/* Alarm */

void alarm_trigger() {
  client.publish(make_topic("alarm"), pot_id);
  state_alarm();
}

