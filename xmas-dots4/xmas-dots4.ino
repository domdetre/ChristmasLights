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
  LEDS.setBrightness(50);
  Serial.println("booted");
  clearStrip();
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void loop() {
  int count = random(20, 50);
  for (int c = 0; c < count; c++) {
    int ledIndex = random(NUM_LEDS);
    bool isLid = (leds[ledIndex].r != 0 || leds[ledIndex].g != 0 || leds[ledIndex].b != 0);

   // Serial.println("ledIndex:"+String(ledIndex)+" isLid:"+String(isLid));

//    if (isLid) 
//    {
//      //leds[ledIndex] = CRGB::Black;
//    } 
//    else 
//    {
      //Serial.println(String(ledIndex % 8));

      // GRB
      //switch (random(8)) {
      switch (random(4)) {
        case 0:
          // blue
          leds[ledIndex] = CRGB(0, 0, 255);
          break;
        case 1:
          //red
          leds[ledIndex] = CRGB(0, 255, 0);
          break;
        case 2:
          // green
          leds[ledIndex] = CRGB(255, 0, 0);
          break;
        case 3:
          // orange
          leds[ledIndex] = CRGB(150, 255, 0);
          break;
        default:
          // white
          leds[ledIndex] = CRGB(50,50,50);
      }
    //}
  }
    
  LEDS.show();
}

void clearStrip() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    leds[ledIndex] = CRGB::Black;
  }
  
  LEDS.show();
}
