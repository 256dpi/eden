class Pot {
  String id;
  
  float moisture = 0;
  float temperature = 0;
  float light = 0;

  int infoStep = 0;
  int infoSpeed = 4000;
  int infoTime = 0;
  
  Pot(String _id) {
    this.id = _id;
  }
  
  void loop() {
    if(millis() - infoSpeed > infoTime) {
      if(infoStep == 1) {
        client.publish(id + "/state/moisture", Integer.toString(round(moisture / 100.0 * 16.0)));
        info(2);
      } else if(infoStep == 2) {
        client.publish(id + "/state/light", Integer.toString(round(light / 100.0 * 16.0)));
        info(3);
      } else if(infoStep == 3) {
        client.publish(id + "/state/sleep");
        info(0);
      }
    }
  }
  
  void info(int step) {
    infoStep = step;
    infoTime = millis();
  }
  
  void draw(int y) {  
    text("M: " + moisture + "%", width/2, y + 50);
    text("C: " + temperature + "°", width/2, y + 100);
    text("L: " + light + "%", width/2, y + 150);
  }
  
  void wake() {
    client.publish(id + "/state/wake");
    info(1);
  }
  
  void alarm(boolean on, boolean forward) {
    if(on) {
      if(forward) {
        client.publish(id + "/alarm/forward");
      } else {
        client.publish(id + "/alarm/on"); 
      } 
    } else {
      client.publish(id + "/alarm/off");
    }
  }
  
  void handle(String[] segments, byte[] payload) {
    if(segments[1].equals("data")) {
      if(segments[2].equals("moisture.n")) {
        moisture = Float.parseFloat(new String(payload));
      } else if(segments[2].equals("temperature.n")) {
        temperature = Float.parseFloat(new String(payload));
      } else if(segments[2].equals("light.n")) {
        light = Float.parseFloat(new String(payload));
      }
    } else if(segments[1].equals("touch")) {
      client.publish(id + "/state/wake");
      info(1);
      // if(segments[2].equals("short")) {}
    }
  }
}