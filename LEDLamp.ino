#include <FastLED.h>
#define DATA_PIN 2
#define NUM_LEDS 32

CRGB leds[NUM_LEDS];

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void printValues(int analogVal, float voltageVal, float brightness) {
  Serial.print("Analog: ");
  Serial.print(analogVal);
  
  Serial.print(", Voltage: ");
  Serial.print(voltageVal);
  
  Serial.print(", Brightness: ");
  Serial.println(brightness);
}

void setRGBs() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 255, 255);
//    leds[i] = CRGB(255, 0, 0);
//    leds[i] = CRGB(0, 255, 0);
//    leds[i] = CRGB(0, 0, 255);
  }
  FastLED.show();
}

void setup() {
  Serial.begin(9600);
  
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,35 * NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  int analogVal = analogRead(A0);
  // Rescale to potentiometer's voltage (from 0V to 5V):
  float voltage = floatMap(analogVal, 0, 1023, 0, 5);
  float brightness = analogVal/3.84; //set brightness between 0 & 255
  if (brightness > 255) {
    brightness = 255; //max brightness
  }
  else if (brightness < 30) {
    brightness = 30; //min brightness
  }
  FastLED.setBrightness(brightness);
  setRGBs();
  printValues(analogVal, voltage, brightness);
}
