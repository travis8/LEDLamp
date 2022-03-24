#include <FastLED.h>
#define DATA_PIN 2
#define NUM_LEDS 32

CRGB leds[NUM_LEDS];
float curBrightness = 0.0;

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void printBrightnessValues(int analogVal, float voltageVal, float brightness) {
  Serial.print("Analog: ");
  Serial.print(analogVal);
  
  Serial.print(", Voltage: ");
  Serial.print(voltageVal);
  
  Serial.print(", Brightness: ");
  Serial.println(brightness);
}

void printRGBValues(float r, float g, float b) {
  Serial.print("R: ");
  Serial.print(r);
  
  Serial.print(", G: ");
  Serial.print(g);
  
  Serial.print(", B: ");
  Serial.println(b);
}

void setRGB(float rVal, float gVal, float bVal) {
  //min and max analog values are 0 and 1023 for the potentiometers I'm using
  float red = floatMap(rVal, 0.0, 1023.0, 10.0, 255.0);
  float green = floatMap(gVal, 0.0, 1023.0, 10.0, 255.0);
  float blue = floatMap(bVal, 0.0, 1023.0, 10.0, 255.0);
  
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(red, green, blue);
  }
  FastLED.show();

  printRGBValues(rVal, gVal, bVal);
  printRGBValues(red, green, blue);
}

void setLEDBrightness(int analogBrightnessVal){
  // Rescale to potentiometer's voltage (from 0V to 5V):
  float voltage = floatMap(analogBrightnessVal, 0.0, 1023.0, 0.0, 5.0);
  //map brightness to range 30-255
  float brightness = floatMap(analogBrightnessVal, 0.0, 1023.0, 30.0, 255.0);
  
  if (abs(brightness - curBrightness) > 1){
    curBrightness = brightness;
    FastLED.setBrightness(curBrightness);
  }
  
  printBrightnessValues(analogBrightnessVal, voltage, curBrightness);
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
  int analogBVal = analogRead(A1);
  int analogGVal = analogRead(A2);
  int analogRVal = analogRead(A3);
  
  setLEDBrightness(analogBrightnessVal);
  setRGB(analogRVal, analogGVal, analogBVal);
}
