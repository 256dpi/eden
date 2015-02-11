#include <Bridge.h>
#include <YunClient.h>
#include <MQTTClient.h>

#define IN 0
#define F1 6
#define F2 7
#define T 1000
#define LED 13

YunClient net;
MQTTClient client("connect.shiftr.io", 1883, net);

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  pinMode(F1, OUTPUT);
  pinMode(F2, OUTPUT);
  digitalWrite(LED, LOW);
  
  Serial.println("connecting...");
  if (client.connect("moisture", "5938e5400448b62b", "e53d9b341079b265ec2ea7a3da6a6fe0")) {
    Serial.println("connected!");
    digitalWrite(LED, HIGH);
  } else {
    Serial.println("not connected!");
  }
}

void loop() {
  client.loop();
  
  flip(true);
  delay(T);
  int v1 = analogRead(IN);
  
  flip(false);
  delay(T);
  int v2 = 1023 - analogRead(IN);
  
  int avg = (v1 + v2) / 2;
  client.publish("/moisture.n", String(avg));
}

void flip(boolean flip){
  if(flip){
    digitalWrite(F1, HIGH);
    digitalWrite(F2, LOW);
  }else{
    digitalWrite(F1, LOW);
    digitalWrite(F2, HIGH);
  }
}

void messageReceived(String topic, char * payload, unsigned int length) {}
