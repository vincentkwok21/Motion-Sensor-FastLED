/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
#include <FastLED.h>
#define NUM_LEDS 16
#define LED_PIN 2
uint8_t hue = 108;
int distance;
CRGB leds [NUM_LEDS];
VL53L0X sensor;
int brightness = 10;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
  FastLED.setCorrection (TypicalPixelString);
  Serial.print(sensor.readRangeContinuousMillimeters());
    Serial.println();
  Serial.print(hue);
  Serial.println();
  distance = sensor.readRangeContinuousMillimeters();
  hue = distance / 4;
  
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(170, hue, 255);
  }
    if ( ( 2000 / 8) - ( distance / 8)< 0) {
    brightness = 0;
  }else {
     brightness = (2000 / 8) - 2 * ( distance / 8 ); 
  }
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  FastLED.setBrightness(brightness);
  FastLED.show();
}