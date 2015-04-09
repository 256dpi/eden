class Pot {
  String id;
  
  float moisture = 0;
  float temperature = 0;
  float light = 0;
  String touch = "";
  int channel = 0;
 
  Integer touchTime = 0;  
  
  Pot(String _id) {
    this.id = _id;
  }
  
  void loop() {
    if(touch != "" && millis() - 2000 > touchTime) {
      touch = "";
    }
  }
  
  void draw(int y) {  
    text("M: " + moisture + "%", width/2, y + 50);
    text("C: " + temperature + "°", width/2, y + 100);
    text("L: " + light + "%", width/2, y + 150);
    text("T: " + touch + " C: " + channel, width/2, y + 200);
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
      touch = segments[2];
      touchTime = millis();
    } else if(segments[1].equals("channel")) {
      channel = parseInt(new String(payload));
    } 
  }
}
