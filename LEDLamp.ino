#include <FastLED.h>
#define DATA_PIN 2
#define NUM_LEDS 16

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,500);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  leds[0] = CRGB(255, 0, 0);
  leds[1] = CRGB(0, 255, 0);
  leds[2] = CRGB(0, 0, 255);
//  FastLED.show();
}
