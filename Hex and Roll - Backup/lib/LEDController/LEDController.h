#ifndef  _LED_CONTROLLER_H
#define  _LED_CONTROLLER_H

#include <FastLED.h>

#define NUM_LEDS 156
#define NUM_LEDS2 70

#define END_LED_1 26
#define END_LED_2 52
#define END_LED_3 78
#define END_LED_4 104
#define END_LED_5 130
#define END_LED_6 156

#define END_LED2_1 12
#define END_LED2_2 24
#define END_LED2_3 35
#define END_LED2_4 47
#define END_LED2_5 59
#define END_LED2_6 70

// Number of separate Modules (linked to balls)
#define NUM_MODULES 6

class LEDController {
public: 
LEDController(){};
~LEDController(){cleanup();};

uint8_t end_led2_array[7] = {0, END_LED2_1, END_LED2_2, END_LED2_3, END_LED2_4, END_LED2_5, END_LED2_6};

void setup(const int led_pin, const int led_pin2); // call in setup
void update(); // call in every loop you want to update the LEDs in.

void setColorUpTo(int end_led, CRGB color);
void setColorForBallCombination(CRGB color1, CRGB color2, CRGB color3, CRGB color4, CRGB color5, CRGB color6);
void setBrightness(int brightness);
void setInnerColor(CRGB Color1, CRGB Color2, CRGB Color3, int32_t *p1, int32_t *p2, int32_t *p3, int32_t *p4, int32_t *p5, int32_t *p6);
void setColorIndicators(CRGB *colors, uint8_t indicator_pos[][2]); // array of [6] colors and array of [6][2] indicator positions as inputs

private:
CRGB leds_array[NUM_LEDS];
CRGB leds_array2[NUM_LEDS2];
void cleanup();

};

#endif //_LED_CONTROLLER_H



