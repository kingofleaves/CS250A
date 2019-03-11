#ifndef  _LED_CONTROLLER_H
#define  _LED_CONTROLLER_H

#include <FastLED.h>

#define NUM_LEDS 156

#define END_LED_1 26
#define END_LED_2 52
#define END_LED_3 78
#define END_LED_4 104
#define END_LED_5 130
#define END_LED_6 156

class LEDController {
public: 
LEDController(){};
~LEDController(){cleanup();};

void setup(const int led_pin); // call in setup
void update(); // call in every loop you want to update the LEDs in.

void setColorUpTo(int end_led, CRGB color);
void setColorForBallCombination(CRGB color1, CRGB color2, CRGB color3, CRGB color4, CRGB color5, CRGB color6);
void setBrightness(int brightness);

private:
CRGB leds_array[NUM_LEDS];

void cleanup();

};

#endif //_LED_CONTROLLER_H



