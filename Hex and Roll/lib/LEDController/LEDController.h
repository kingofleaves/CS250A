#ifndef  _LED_CONTROLLER_H
#define  _LED_CONTROLLER_H

#include <FastLED.h>

#define NUM_LEDS 60
#define NUM_MODULES 6

class LEDController {
public: 
LEDController(){};
~LEDController(){cleanup();};

void setup(); // call in setup
void update(); // call in every loop you want to update the LEDs in.

void setColorAllModules(CRGB color);
void setColorOneModule(int module_index, CRGB color);
void LEDController::setColorForBallCombination(CRGB color1, CRGB color2, CRGB color3);

private:
CRGB leds_array[NUM_MODULES][NUM_LEDS];

void cleanup();

};

#endif _LED_CONTROLLER_H



