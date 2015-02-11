#include <Adafruit_NeoPixel.h>

#define PRE 100

Adafruit_NeoPixel animation_pixels = Adafruit_NeoPixel(16, RING);
unsigned long long animation_last_step = 0;
int animation_interval = 0;

typedef struct {
  int r = 0;
  int g = 0;
  int b = 0;
  int cr = 0;
  int cg = 0;
  int cb = 0;
  int s = 0;
} animation_pixel;

animation_pixel animation_state[16];

void animation_start(int interval) {
  animation_interval = interval;
  animation_pixels.begin(); 
}

void animation_all(int r, int g, int b, int d) {
  for(int i=0; i<NUM; i++) {
    animation_one(i, r, g, b, d);
  }
}

void animation_one(int i, int r, int g, int b, int d) {
  if(d < animation_interval) {
    d = animation_interval;
  }
  
  animation_pixel* p = &animation_state[i];
  p->s = d / animation_interval;
  p->cr = (r * PRE - p->r) / p->s;
  p->cg = (g * PRE - p->g) / p->s;
  p->cb = (b * PRE - p->b) / p->s;
}

void animation_loop() {
  if(animation_last_step + animation_interval < millis()) {
    animation_step();
    animation_last_step = millis();
  }
}

void animation_step() {
  boolean dirty = false;
  
  for(int i=0; i<NUM; i++) {
    animation_pixel* p = &animation_state[i];
    
    if(p->s > 0) {
      p->r = p->r + p->cr;
      p->g = p->g + p->cg;
      p->b = p->b + p->cb;
      
      animation_pixels.setPixelColor(i, animation_pixels.Color(p->r / PRE, p->g / PRE, p->b / PRE));
      dirty = true;
      p->s--;
    }
  }
  
  if(dirty) {
    animation_pixels.show();
  }
}
