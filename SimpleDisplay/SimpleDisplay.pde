import processing.mqtt.*;

MQTTClient client;

String value;

void setup() {
  size(200, 150);
  client = new MQTTClient(this);
  client.connect("mqtt://5938e5400448b62b:e53d9b341079b265ec2ea7a3da6a6fe0@connect.shiftr.io", "eden2");
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

void messageReceived(String topic, byte[] payload) {
  value = new String(payload);
}
