#include <FastLED.h>
#define NUM_LEDS 16
#define LED_PIN 2
const int trigPin = 9;
const int echoPin = 10;
uint8_t hue = 108;
long duration;
int distance;
CRGB leds [NUM_LEDS];

uint8_t paletteIndex = 0;
// Gradient palette "moon_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/pn/tn/moon.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 188 bytes of program space.
// Gradient palette "usgs_feet_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/usgs/tn/usgs-feet.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 88 bytes of program space.
 // Gradient palette "GMT_hot_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_hot.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( GMT_hot_gp ) {
    0,   0,  0,  0,
   95, 255,  0,  0,
  191, 255,255,  0,
  255, 255,255,255};

CRGBPalette16 myPal = GMT_hot_gp;
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
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  hue = distance * 10;
   Serial.print("Distance: ");
  Serial.println(distance);
    FastLED.setCorrection (TypicalPixelString);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(255, hue, 255);
  }
  FastLED.show();
}
