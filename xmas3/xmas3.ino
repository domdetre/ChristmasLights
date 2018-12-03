#include <FastLED.h>


FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    300
#define SECOND_PER_ANI 20

//CRGB leds[NUM_LEDS];
CRGBArray<NUM_LEDS> leds;

#define BRIGHTNESS          150
#define FRAMES_PER_SECOND  120

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { rattleSnakes };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void fastledDelay(int fps = 25) {
  FastLED.delay(1000 / fps);
}

void resetLeds() {
  for (int i = 0; i < 10; i++) {
    leds.fadeToBlackBy(30);
    fastledDelay();
  }

  FastLED.show();
  FastLED.delay(500);
}


// ================================================================================================================
void setup() {
  delay(1000);

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}



// ================================================================================================================

//void nextPattern()
//{
//  // add one to the current pattern number, and wrap around at the end
//  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
//}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter)
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti(int durationSeconds = 10, int speed = 25)
{
  unsigned long end = millis() + (durationSeconds * 1000);

  // random colored speckles that blink in and fade smoothly
  while(end > millis()) {
    leds.fadeToBlackBy(10);
    leds[random16(NUM_LEDS)] += CHSV(random8(), 200, 255);
    fastledDelay(speed);
  }
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle(int durationSeconds = 10, int speed = 25) {
  unsigned long end = millis() + (durationSeconds * 1000);

  while(end > millis()) {
    // eight colored dots, weaving in and out of sync with each other
    leds.fadeToBlackBy(20);
    byte dothue = 0;
    for( int i = 0; i < 8; i++) {
      leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }

    fastledDelay(speed);
  }
}

void twoSnakes(int repeat = 1, int speed = 25) {
  static uint8_t hue;
  for(int r = 0; r < repeat; r++) {
    for(int i = 0; i < NUM_LEDS/2; i++) {
      // fade everything out
      leds.fadeToBlackBy(40);

      // let's set an led value
      leds[i] = CHSV(hue++,255,255);

      // now, let's first 20 leds to the top 20 leds,
      leds(NUM_LEDS/2,NUM_LEDS-1) = leds(NUM_LEDS/2 - 1 ,0);

      fastledDelay(speed);
    }
  }
}

void rattleSnakes(int repeat = 1, int fps = 25) {
  static uint8_t hue;
  static int medianIndex = NUM_LEDS/2;
  static int target = medianIndex * repeat;
  for(int i = 0; i < target; i++) {
    // fade everything out a bit
    leds.fadeToBlackBy(40);

    // increment the color
    hue++;

    int ledIndexSecondary = i;
    while (ledIndexSecondary >= 0) {
      if (ledIndexSecondary < medianIndex) {
        leds[ledIndexSecondary] = CHSV(hue,255,255);
      }

      ledIndexSecondary -= 30;
    }

    // mirror the first half on the second half of the strip
    leds(medianIndex, NUM_LEDS-1) = leds(medianIndex - 1 ,0);

    fastledDelay(fps);
  }
}



// ================================================================================================================
void loop()
{
  resetLeds();
  confetti(30, 100);

  resetLeds();
  juggle(30, 25);

  resetLeds();
  rattleSnakes(5, 25);
}
