/**
 * Pot - Pot Controller
 *
 * Eden Project: A networked pot.
 */

#include <Bridge.h>
#include <YunClient.h>
#include <MQTTClient.h>

boolean isConnected = false;
boolean isAnimated = false;

YunClient net;
MQTTClient client("connect.shiftr.io", 1883, net);

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  
  Serial.println("Hello Pot!");
  
  moisture_setup();
  ring_setup();
  touch_setup();

  if(client.connect("pot1", "5938e5400448b62b", "e53d9b341079b265ec2ea7a3da6a6fe0")) {
    client.subscribe("/ring/+");
    
    isConnected = true;
    ring_all(255, 255, 255, 1000);
  }
}

void loop() {
  if(isConnected) {
    client.loop();
    moisture_loop();
    ring_loop();
    touch_loop();
    
    if(!isAnimated && millis() > 5000) {
      ring_all(0, 0, 0, 500);
      isAnimated = true;
    }
  } 
}

/* MQTTClient */

void messageReceived(String topic, char * payload, unsigned int len) {
  if(topic.equals("/ring/off")) {
    ring_all(0, 0, 0, 100);
  } else if(topic.equals("/ring/on")) {
    ring_all(255, 255, 255, 100);
  } else if(topic.equals("/ring/wake")) {
    ring_all(50, 50, 50, 500);
  } else if(topic.equals("/ring/sleep")) {
    ring_all(0, 0, 0, 500);
  } else if(topic.equals("/ring/display")) {
    char str[len+1];
    memcpy(str, payload, len); 
    str[len] = '\0';
    int value = String(str).toInt();
    
    for(int i=0; i<16; i++) {
      if(i < value) {
        ring_one(i, 0, 0, 255, 500);
      } else {
        ring_one(i, 0, 0, 0, 500);
      }
    }
  }
}

/* Moisture */

void moisture_read(int value) {
  client.publish("/moisture.n", String(value));
}

/* Touch */

void touch_on(int pin) {
  if(pin == 0) {  
    client.publish("/touch/on");
  }
}

void touch_off(int pin) {
  if(pin == 0) {
    client.publish("/touch/off");
  }
}

