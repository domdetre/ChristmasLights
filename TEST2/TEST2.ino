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
bool modes[0];
//short hues[NUM_LEDS];

#define ModeInactive 1
#define ModeActive 2
#define ModeFadeIn 3
#define ModeFadeOut 4

#define FadeStep 10

void setup() { 
  LEDS.addLeds<WS2812B,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(84);
  
  clearStrip();
}

void loop() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    
    if (modes[ledIndex] == ModeActive) {
      if (random8() < 128) {
        modes[ledIndex] = ModeFadeOut;
      }
    }
    
    if (modes[ledIndex] == ModeInactive) {
      if (random8() < 128) {
        modes[ledIndex] = ModeFadeIn;
        //hues[ledIndex] = random8();
        //leds[ledIndex] = CHSV(hues[ledIndex], 255, 255);
      }
    }

    if (modes[ledIndex] == ModeFadeIn) {
//      brights[ledIndex] += BrightStep;
//      if (brights[ledIndex] > 255) {
//        brights[ledIndex] = 255;
//        modes[ledIndex] = ModeActive;
//      }
      //leds[ledIndex] = CHSV(hues[ledIndex], 255, 255);
    }

    if (modes[ledIndex] == ModeFadeOut) {
      //leds[ledIndex] = CHSV(hues[ledIndex], 255, 255);
//      brights[ledIndex] -= BrightStep;
//      if (brights[ledIndex] < 0) {
//        brights[ledIndex] = 0;
//        modes[ledIndex] = ModeInactive;
//      }
    }

    //leds[ledIndex] = CHSV(hues[ledIndex], 255, 255);
  }

  LEDS.show();
}

void clearStrip() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    leds[ledIndex] = CRGB::Black;
//    hues[ledIndex] = 0;
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
