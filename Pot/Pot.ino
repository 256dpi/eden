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
#include <YunClient.h>
#include <MQTTClient.h>

const char * id = ID;
const char * key = KEY;
const char * secret = SECRET;

boolean online = false;
boolean booted = false;

char topic_buffer[32];

YunClient net;
MQTTClient client("connect.shiftr.io", 1883, net);

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  
  ring_setup();
  touch_setup();

  if(client.connect(id, key, secret)) {
    client.subscribe(make_topic("state/+"));
    client.subscribe(make_topic("alarm/+"));
    
    online = true;
    ring_all(255, 255, 255, 1000);
  } else {
    ring_all(255, 0, 0, 1000);
  }
}

void loop() {
  if(online) {
    client.loop();
    moisture_loop();
    ring_loop();
    touch_loop();
    temperature_loop();
    light_loop();
    alarm_loop();
    
    if(!booted && millis() > 5000) {
      ring_all(0, 0, 0, 500);
      booted = true;
    }
  } 
}

const char * make_topic(const char * string) {
  int id_len = strlen(id);
  strcpy(topic_buffer, id);
  topic_buffer[id_len] = '/';
  strcpy(topic_buffer + id_len + 1, string);
  return topic_buffer;
}

/* MQTTClient */

void messageReceived(String topic, String payload, char * bytes, unsigned int len) {  
  if(topic.equals(make_topic("state/wake"))) {
    state_wake();
  } else if(topic.equals(make_topic("state/moisture"))) {
    state_moisture(payload.toInt());
  } else if(topic.equals(make_topic("state/light"))) {
    state_light(payload.toInt());
  } else if(topic.equals(make_topic("state/sleep"))) {
    state_sleep();
  } else if(topic.equals(make_topic("alarm/on"))) {
    alarm_on(false);
  } else if(topic.equals(make_topic("alarm/forward"))) {
    alarm_on(true);
  } else if(topic.equals(make_topic("alarm/off"))) {
    alarm_off();
  }
}

/* Moisture */

void moisture_change(float value) {
  client.publish(make_topic("data/moisture.n"), String(value));
}

/* Touch */

void touch_short() {
  client.publish(make_topic("touch/short"));
}

void touch_long() {
  client.publish(make_topic("touch/long"));
}

/* Temperature */

void temperature_change(float value) {
  client.publish(make_topic("data/temperature.n"), String(value));
}

/* Light */

void light_change(float value) {
  client.publish(make_topic("data/light.n"), String(value));
}

