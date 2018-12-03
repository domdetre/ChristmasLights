#include <FastLED.h>
#define DATA_PIN     3
#define NUM_LEDS    300
#define FPS         25

CRGB leds[NUM_LEDS];
//star1 = new Star(15,20, 0);

void setup() {
  delay(1000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  fillRandomAll(100);
  FastLED.show();
  delay(1000 / FPS);
}

void setColorSection(CRGB color, int start, int end) {
  for (int lednumber = start-1; lednumber < end; lednumber++) {
    leds[lednumber] = color;
  }
}

// switches on all LEDs. Each LED is shown in random color.
// numIterations: indicates how often LEDs are switched on in random colors
void fillRandomAll(int numIterations) {
  for (int iteration = 0; iteration < numIterations; ++iteration) {
    for (int i = 0; i < NUM_LEDS; ++i) {
      leds[i] = CHSV(random8(),255,255); // hue, saturation, value
    }
  }
}
