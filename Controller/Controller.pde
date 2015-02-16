/**
 * Controller - System Controller
 *
 * Eden Project: A networked pot.
 */

import processing.mqtt.*;

MQTTClient client;

float moisture = 0;
float temperature = 0;
boolean touch = false;
float light = 0;
String lastColor = "r";

int infoStep = 0;
int infoSpeed = 4000;
int infoTime = 0;

void setup() {
  size(300, 280);
  client = new MQTTClient(this);
  client.connect("mqtt://5938e5400448b62b:e53d9b341079b265ec2ea7a3da6a6fe0@connect.shiftr.io", "controller");
  client.subscribe("/moisture.n");
  client.subscribe("/temperature.n");
  client.subscribe("/light.n");
  client.subscribe("/touch/+");
  
  fill(0);
  textSize(40);
  textAlign(CENTER);
}

void draw() {
  if(millis() - infoSpeed > infoTime) {
    if(infoStep == 1) {
      client.publish("/ring/display-b", Integer.toString(round(moisture / 100.0 * 16.0)));
      info(2);
    } else if(infoStep == 2) {
      client.publish("/ring/display-y", Integer.toString(round(light / 100.0 * 16.0)));
      info(3);
    } else if(infoStep == 3) {
      client.publish("/state/sleep");
      info(0);
    }
  }
  
  background(255);
  text("M: " + moisture + "%", width/2, 50);
  text("C: " + temperature + "°", width/2, 100);
  text("T: " + touch, width/2, 150);
  text("L: " + light + "%", width/2, 200);
  text("I: " + infoStep, width/2, 250);
}

void keyPressed() {
  if(keyCode == 37) {
    client.publish("/state/sleep");
  } else if(keyCode == 39) {
    client.publish("/state/wake");
  } else if(keyCode == 33) {
    client.publish("/alarm/on");
  } else if(keyCode == 34) {
    client.publish("/alarm/off");
  } else if(keyCode == 82) {
    lastColor = "r";
  } else if(keyCode == 71) {
    lastColor = "g";
  } else if(keyCode == 66) {
    lastColor = "b";
  } else if(keyCode >= 48 && keyCode <= 57) {
    client.publish("/ring/display-" + lastColor, Integer.toString((keyCode - 48) * 2));
  } else {
    println(keyCode);
  }
}

void messageReceived(String topic, byte[] payload) {
  if(topic.equals("/moisture.n")) {
    moisture = Float.parseFloat(new String(payload));
  } else if(topic.equals("/temperature.n")) {
    temperature = Float.parseFloat(new String(payload));
  }  else if(topic.equals("/light.n")) {
    light = Float.parseFloat(new String(payload));
  } else if(topic.equals("/touch/on")) {
    touch = true;
    client.publish("/state/wake");
    info(1);
  } else if(topic.equals("/touch/off")) {
    touch = false;
  }
}

void info(int step) {
  infoStep = step;
  infoTime = millis();
}
