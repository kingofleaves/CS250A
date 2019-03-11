#ifndef  _LED_CONTROLLER_H
#define  _LED_CONTROLLER_H

#include <FastLED.h>

#define NUM_LEDS 156

class LEDController {
public: 
LEDController(){};
~LEDController(){cleanup();};

void setup(const int led_pin); // call in setup
void update(); // call in every loop you want to update the LEDs in.

void setColorUpTo(int end_led, CRGB color);
void setColorForBallCombination(CRGB color1, CRGB color2, CRGB color3);
void setBrightness(int brightness);

private:
CRGB leds_array[NUM_LEDS];

void cleanup();

};

#endif //_LED_CONTROLLER_H



