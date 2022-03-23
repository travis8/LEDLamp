#include <FastLED.h>
#define DATA_PIN 2
#define NUM_LEDS 32

CRGB leds[NUM_LEDS];
float curBrightness = 0.0;

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

void setRGB() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 255, 255);
//    leds[i] = CRGB(255, 0, 0);
//    leds[i] = CRGB(0, 255, 0);
//    leds[i] = CRGB(0, 0, 255);
  }
  FastLED.show();
}

void setLEDBrightness(int analogBrightnessVal){
  // Rescale to potentiometer's voltage (from 0V to 5V):
  float voltage = floatMap(analogBrightnessVal, 0, 1023, 0, 5);
  //map brightness to range 30-255
  float brightness = analogBrightnessVal / (float)1023 * (255 - 30) + 30;
  
  if (abs(brightness - curBrightness) > 1){
    curBrightness = brightness;
    FastLED.setBrightness(curBrightness);
    Serial.println("changing");
  }
  
  printValues(analogBrightnessVal, voltage, curBrightness);
}

void setup() {
  Serial.begin(9600);
  
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,35 * NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  int analogBrightnessVal = analogRead(A0);
  setLEDBrightness(analogBrightnessVal);
  setRGB();
}
