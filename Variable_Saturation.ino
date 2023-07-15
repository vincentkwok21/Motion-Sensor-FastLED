#include <FastLED.h>
#define NUM_LEDS 16
#define LED_PIN 2
const int trigPin = 9;
const int echoPin = 10;
uint8_t hue = 108;
long duration;
int distance;
CRGB leds [NUM_LEDS];
int stabilization[3] = {};
int distance_readings_counter = 0;
int brightness = 10;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if (distance < 90) {
    stabilization[distance_readings_counter % 3] = distance;
    distance_readings_counter++;
  } else {
    distance = stabilization[distance_readings_counter % 3];
  }
 
  hue = distance * 2.5;
   Serial.print("Distance: ");
  Serial.println(distance);
    FastLED.setCorrection (TypicalPixelString);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(170, hue, 255);
  }
  if ( 80 - distance < 0) {
    brightness = 0;
  }else {
     brightness = 80-distance; 
  }
  FastLED.setBrightness(brightness);
  FastLED.show();
}
