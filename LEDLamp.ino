#include <FastLED.h>
#define DATA_PIN 2
#define NUM_LEDS 32

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,35 * NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  FastLED.setBrightness(255);
}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 255, 255);
  }
  FastLED.show();
}
