#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 300 

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3

#define FPS 25

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  Serial.begin(57600);
  LEDS.addLeds<WS2812B,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(84);
  Serial.println("booted");
  clearStrip();
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void loop() {
  // random8()
  
  int ledIndex = 10;
  int hue = 100;

  // show a new star?
  lightUpOneStar(ledIndex, hue, 10);
  delay(1000);

  // fade away a star?
  lightDownOneStar(ledIndex);
  delay(1000);
}

void clearStrip() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    leds[ledIndex] = CRGB::Black;
  }
  
  LEDS.show();
}

void fillStrip() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    leds[ledIndex] = CHSV(random(255), 255, 255);
  }
  
  LEDS.show();
}

void fillRandomStrip() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    if (random(2) < 1) {
      leds[ledIndex] = CHSV(random(255), 255, 255);
    } else {
      leds[ledIndex] = CRGB::Black;
    }
  }
  
  LEDS.show();
}

void lightUpOneStar(int ledIndex, int hue, int brightStep) {
  Serial.println("lightUpOneStar" + String(ledIndex) + " hue " + String(hue));
  leds[ledIndex] = CHSV(hue, 255, 10);
  LEDS.show();
  delay(1000);
  
  for (int bright = 0; bright < 256; bright+=brightStep) {
    leds[ledIndex] = CHSV(hue, 255, bright);
    LEDS.show();
    delay(1);
  }
}

void lightDownOneStar(int ledIndex) {
  Serial.println("lightDownOneStar" + String(ledIndex));

  int brightStep = 10;
  for (int bright = 0; bright < 256; bright+=brightStep) {
    leds[ledIndex].fadeToBlackBy(brightStep);
    LEDS.show();
    delay(1);
  }

  leds[ledIndex] = CRGB::Black;
  LEDS.show();
}
