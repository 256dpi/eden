import processing.mqtt.*;

MQTTClient client;

String value;

void setup() {
  size(200, 150);
  client = new MQTTClient(this);
  client.connect("mqtt://5938e5400448b62b:e53d9b341079b265ec2ea7a3da6a6fe0@connect.shiftr.io", "controller");
  client.subscribe("/moisture.n");
  value = new String("...");
  
  fill(0);
  textSize(50);
  textAlign(CENTER);
}

void draw() {
  background(255);
  text(value, width/2, height / 2 + 15);
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
  } else {
    println(keyCode);
  }
}

void messageReceived(String topic, byte[] payload) {
  value = new String(payload);
}
