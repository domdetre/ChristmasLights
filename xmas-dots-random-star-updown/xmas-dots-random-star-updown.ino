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
  
  int ledIndex = random(300);
  int hue = random(255);

  // show a new star?
  if (random(100) < 50) {
    lightUpOneStar(ledIndex, hue, random(10, 30));
  }

  // fade away a star?
  if (random(100) < 50) {
    lightDownOneStar(ledIndex);
  }

  delay(random(0,80));
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

void lightUpOneStar(int ledIndex, int hue, int brightStep) {
  Serial.println("lightUpOneStar" + String(ledIndex) + " hue " + String(hue));
  
  for (int bright = 0; bright < 256; bright+=brightStep) {
    leds[ledIndex] = CHSV(hue, 255, bright);
    LEDS.show();
    delay(1);
  }
}

void lightDownOneStar(int ledIndex) {
  //Serial.println("lightDownOneStar" + String(leds[ledIndex].h));
  Serial.println("lightDownOneStar");

  leds[ledIndex].nscale8(250);
  
//  for (int bright = 0; bright < 256; bright++) {
//    leds[ledIndex].fadeToBlackBy(64);
//    LEDS.show();
//    delay(1);
//  }
  leds[ledIndex] = CRGB::Black;
  LEDS.show();
}
