#include <FastLED.h>

//#define DEBUG

// How many leds in your strip?
#define NUM_LEDS 300 

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  #ifdef DEBUG
  Serial.begin(57600);
  #endif
  LEDS.addLeds<WS2812B,DATA_PIN,RGB>(leds,NUM_LEDS);
  Serial.println("booted");
  clearStrip();
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void loop() {
  int ledIndex = random(300);
  int hue = random8();

  bool isLid = (leds[ledIndex].r != 0 || leds[ledIndex].g != 0 || leds[ledIndex].b != 0);

  // show a new star?
  if (isLid) {
    lightDownOneStar(ledIndex, random(100,200));
  } else {
    lightUpOneStar(ledIndex, random(100,200));
  }
}

void clearStrip() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    leds[ledIndex] = CRGB::Black;
  }
  
  LEDS.show();
}

void fillStrip() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    leds[ledIndex] = CHSV(random8(), 255, 255);
  }
  
  LEDS.show();
}

void fillRandomStrip() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    if (random(2) < 1) {
      leds[ledIndex] = CHSV(random8(), 255, 255);
    } else {
      leds[ledIndex] = CRGB::Black;
    }
  }
  
  LEDS.show();
}

void lightUpOneStar(int ledIndex, int brightStep) {
  #ifdef DEBUG
  Serial.print("lightUpOneStar" + String(ledIndex) + " hue:" + String(hue) + " speed:" + String(brightStep));
  #endif

  int hue = random8();
  for (int bright = 0; bright < 256; bright+=brightStep) {
    leds[ledIndex] = CHSV(hue, 255, bright);
    LEDS.show();
  }
  Serial.println();
}

void lightDownOneStar(int ledIndex, int brightStep) {
  #ifdef DEBUG
  Serial.print("lightDownOneStar" + String(ledIndex) + " speed:" + String(brightStep));
  #endif

  for (int bright = 256; bright > 0; bright-=brightStep) {
    leds[ledIndex].fadeToBlackBy(brightStep);
    LEDS.show();
  }
  
  leds[ledIndex] = CRGB::Black;
  LEDS.show();
  Serial.println();
}
