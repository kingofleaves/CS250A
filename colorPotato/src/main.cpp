#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 60

CRGB leds[NUM_LEDS];

void setup() { 
  FastLED.addLeds<NEOPIXEL, 33>(leds, NUM_LEDS); 
}
void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    int j = abs(i*2 - NUM_LEDS);
	  leds[i] = CRGB(255, (NUM_LEDS - j)*2, (NUM_LEDS - j)*2); FastLED.show();
  }
  delay(100);
  for (int i = 0; i < NUM_LEDS; i++) { 
	  leds[i] = CRGB::Black; FastLED.show(); 
  }
  delay(100);
}