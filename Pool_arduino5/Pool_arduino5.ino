// Pin layouts on the teensy 3/3.1:
// WS2811_PORTDC: 2,14,7,8,6,20,21,5,15,22,23,9,10,13,11,12 - 16 way parallel

#include<FastLED.h>

#define NUM_LEDS_PER_STRIP 144
#define NUM_STRIPS 16
#define AMPLITUDE 60
#define PHASE_Z_SCALE 0.75
#define PHASE_X_SCALE 0
 
const float PERIOD = 300.0;

int pixel[NUM_STRIPS];
int lastPixel[NUM_STRIPS];;
float phase = 0;
long time = 0;

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

void setup() {
  LEDS.addLeds<WS2811_PORTDC, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP);
  Serial.begin(9600);
  for (int i = 0; i < NUM_STRIPS; i++) {
    lastPixel[i] = 0;
  }
  //  LEDS.setBrightness(32);
}

void loop() {

  time = millis();
  for (int i = 0; i < NUM_STRIPS; i++) {
    phase = PHASE_Z_SCALE * (i / 4 * PI/4.0 + PHASE_X_SCALE * ((i % 4) * PI / 9.0));  //making use of integer division to add up to 3/4PI radians of phase by row and 3/8PI radians of phase by column
    pixel[i] = int(AMPLITUDE  * (sin(time / PERIOD + phase) + 1.0) + NUM_LEDS_PER_STRIP / 2 - AMPLITUDE);
    //check if the value of pixel[i] changed to prevent flickering from black to blue at the top and bottom of the sine wave
    if (pixel[i] != lastPixel[i]) {
      leds[(i * NUM_LEDS_PER_STRIP) + pixel[i]] = CRGB::Blue;
      leds[(i * NUM_LEDS_PER_STRIP) + lastPixel[i]] = CRGB::Black;
      lastPixel[i] = pixel[i];
      Serial.println(pixel[i]);
    }  
  }
  LEDS.show();


// 
//    int pixel;
//    pixel = int(NUM_LEDS_PER_STRIP / 2  * (sin(millis() / 800.0) + 1.0));
//    if (pixel != lastPixel) {
//      for (int i = 0; i < NUM_STRIPS - 1; i++) {
//        leds[(i * NUM_LEDS_PER_STRIP) + pixel] = CRGB::Blue;
//        leds[(i * NUM_LEDS_PER_STRIP) + lastPixel] = CRGB::Black;
//      }
//      LEDS.show();
//      lastPixel = pixel;
//      Serial.println(pixel);
//    }
}
