/**
 * Controller - System Controller
 *
 * Eden Project: A networked pot.
 */

import processing.mqtt.*;

MQTTClient client;

ArrayList<Pot> pots;

void setup() {
  pots = new ArrayList<Pot>(3);
  
  pots.add(new Pot("pot1"));
  pots.add(new Pot("pot2"));
  pots.add(new Pot("pot3"));
  
  size(300, pots.size() * 200);
  
  client = new MQTTClient(this);
  client.connect("mqtt://5938e5400448b62b:e53d9b341079b265ec2ea7a3da6a6fe0@connect.shiftr.io", "controller");
  client.subscribe("+/data/+");
  client.subscribe("+/touch/+");
  
  fill(0);
  textSize(40);
  textAlign(CENTER);
}

void loop() {
  for(Pot pot: pots) {
    pot.loop();
  }
}

void draw() {
  loop();
  
  background(255);
  
  int y = 15;
  for(Pot pot: pots) {
    pot.draw(y);
    y += 200;
  }
}

void keyPressed() {
  if(keyCode == 10) {
    for(Pot pot: pots) {
      pot.wake();
    }
  } else if(keyCode == 36) {
    for(Pot pot: pots) {
      pot.alarm(true, true);
    }
  } else if(keyCode == 33) {
    for(Pot pot: pots) {
      pot.alarm(true, false);
    }
  } else if(keyCode == 34) {
    for(Pot pot: pots) {
      pot.alarm(false, false);
    }
  } else {
    println(keyCode);
  }
}

void messageReceived(String topic, byte[] payload) {
  String[] segments = topic.split("/");
  
  for(Pot pot: pots) {
    if(pot.id.equals(segments[0])) {
      pot.handle(segments, payload);
    }
  }
}

