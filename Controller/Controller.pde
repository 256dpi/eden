/**
 * Controller - System Controller
 *
 * Eden Project: A networked pot.
 */

import processing.mqtt.*;

MQTTClient client;

String moisture;
String temperature;
String touch;

void setup() {
  size(200, 200);
  client = new MQTTClient(this);
  client.connect("mqtt://5938e5400448b62b:e53d9b341079b265ec2ea7a3da6a6fe0@connect.shiftr.io", "controller");
  client.subscribe("/moisture.n");
  client.subscribe("/temperature.n");
  client.subscribe("/touch/+");
  moisture = new String("..."); 
  temperature = new String("...");
  touch = new String("...");
  
  fill(0);
  textSize(40);
  textAlign(CENTER);
}

void draw() {
  background(255);
  text(moisture, width/2, 50);
  text(temperature, width/2, 100);
  text(touch, width/2, 150);
}

void keyPressed() {
  if(keyCode == 38) {
    client.publish("/ring/on");
  } else if(keyCode == 40) {
    client.publish("/ring/off");
  } else if(keyCode == 37) {
    client.publish("/ring/sleep");
  } else if(keyCode == 39) {
    client.publish("/ring/wake");
  } else if(keyCode >= 48 && keyCode <= 57) {
    client.publish("/ring/display", Integer.toString(keyCode - 48));
  }
}

void messageReceived(String topic, byte[] payload) {
  if(topic.equals("/moisture/n")) {
    moisture = new String(payload);
  } else if(topic.equals("/temperature/n")) {
    temperature = new String(payload);
  } else if(topic.equals("/touch/on")) {
    touch = "on";
    client.publish("/ring/wake");
  } else if(topic.equals("/touch/off")) {
    touch = "off";
    client.publish("/ring/sleep");
  }
}
