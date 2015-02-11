#include <Bridge.h>
#include <YunClient.h>
#include <MQTTClient.h>

#define RING 7
#define NUM 16
#define LED 13

YunClient net;
MQTTClient client("connect.shiftr.io", 1883, net);

boolean start_animation = false;

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  digitalWrite(LED, LOW);
  
  Serial.println("connecting...");
  if (client.connect("ring", "5938e5400448b62b", "e53d9b341079b265ec2ea7a3da6a6fe0")) {
    client.subscribe("/ring/on");
    client.subscribe("/ring/off");
    client.subscribe("/ring/wake");
    client.subscribe("/ring/sleep");
    client.subscribe("/ring/display");
    Serial.println("connected!");
    digitalWrite(LED, HIGH);
  } else {
    Serial.println("not connected!");
  }
  
  animation_start(5);
  animation_all(255, 255, 255, 1000);
}

void loop() {
  client.loop();
  animation_loop();
  
  if(!start_animation && millis() > 5000) {
    animation_all(0, 0, 0, 1000);
    start_animation = true;
  }
}

void messageReceived(String topic, char * payload, unsigned int len) {
  if(topic.equals("/ring/off")) {
    animation_all(0, 0, 0, 100);
  } else if(topic.equals("/ring/on")) {
    animation_all(255, 255, 255, 100);
  } else if(topic.equals("/ring/wake")) {
    animation_all(50, 50, 50, 500);
  } else if(topic.equals("/ring/sleep")) {
    animation_all(0, 0, 0, 500);
  } else if(topic.equals("/ring/display")) {
    char str[len+1];
    memcpy(str, payload, len); 
    str[len] = '\0';
    int value = String(str).toInt();
    
    for(int i=0; i<NUM; i++) {
      if(i < value) {
        animation_one(i, 0, 0, 255, 500);
      } else {
        animation_one(i, 0, 0, 0, 500);
      }
    }
  }
}

