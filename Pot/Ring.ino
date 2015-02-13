/**
 * Ring Animation API
 */

#include <Adafruit_NeoPixel.h>

#define R_CTL 4 // Control Ping
#define R_PRE 100 // Precision
#define R_INT 4 // Update Interval (ms)

Adafruit_NeoPixel ring_pixels = Adafruit_NeoPixel(16, R_CTL);
unsigned long long ring_last_step = 0;

typedef struct {
  int r = 0;
  int g = 0;
  int b = 0;
  int cr = 0;
  int cg = 0;
  int cb = 0;
  int s = 0;
  boolean zero = false;
} ring_pixel;

ring_pixel ring_state[16];

void ring_setup() {
  ring_pixels.begin(); 
}

void ring_all(int r, int g, int b, int d) {
  for(int i=0; i<16; i++) {
    ring_one(i, r, g, b, d);
  }
}

void ring_one(int i, int r, int g, int b, int d) {
  if(d < R_INT) {
    d = R_INT;
  }
  
  ring_pixel* p = &ring_state[i];
  p->s = d / R_INT;
  p->cr = (r * R_PRE - p->r) / p->s;
  p->cg = (g * R_PRE - p->g) / p->s;
  p->cb = (b * R_PRE - p->b) / p->s;
  p->zero = (r == 0 && g == 0 && b == 0);
}

void ring_loop() {
  if(ring_last_step + R_INT < millis()) {
    ring_step();
    ring_last_step = millis();
  }
}

void ring_step() {
  boolean dirty = false;
  
  for(int i=0; i<16; i++) {
    ring_pixel* p = &ring_state[i];
    
    if(p->s > 0) {
      if(p->s == 1 && p->zero) {
        p->r = 0;
        p->g = 0;
        p->b = 0;
        ring_pixels.setPixelColor(i, ring_pixels.Color(0, 0, 0));
      } else {
        p->r = p->r + p->cr;
        p->g = p->g + p->cg;
        p->b = p->b + p->cb;
        ring_pixels.setPixelColor(i, ring_pixels.Color(p->r / R_PRE, p->g / R_PRE, p->b / R_PRE));
      }
      
      dirty = true;
      p->s--;
    }
  }
  
  if(dirty) {
    ring_pixels.show();
  }
}

