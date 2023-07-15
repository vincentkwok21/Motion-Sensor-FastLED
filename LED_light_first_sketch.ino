#include <FastLED.h>
#define NUM_LEDS 16
#define LED_PIN 2

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

DEFINE_GRADIENT_PALETTE( usgs_feet_gp ) {
    0,  41, 90, 25,
    6,  44,112, 32,
   12,  75,139, 42,
   25, 110,173, 42,
   38, 148,191, 74,
   51, 179,209, 89,
   63, 220,219, 87,
   76, 210,189, 78,
   89, 217,166, 57,
  102, 194,130, 54,
  114, 165, 97, 50,
  127, 130, 78, 52,
  140, 167, 97, 74,
  153, 188,122,102,
  165, 179,136,123,
  178, 215,157,170,
  191, 227,175,186,
  204, 224,189,203,
  216, 237,197,201,
  229, 237,209,214,
  242, 232,223,230,
  255, 255,255,255};

DEFINE_GRADIENT_PALETTE( moon_gp ) {
    0,  0, 0, 0,
   128, 255 ,0 , 0,
  200, 255,255,255,
  255, 255, 255, 255
  };

CRGBPalette16 myPal = GMT_hot_gp;
void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

}

void loop() {
  fill_palette(leds, NUM_LEDS, paletteIndex, 255/NUM_LEDS, myPal, 255, LINEARBLEND);
  FastLED.setCorrection (TypicalPixelString);
  FastLED.show();

  EVERY_N_MILLISECONDS(10) {
    paletteIndex ++;
  }
}
