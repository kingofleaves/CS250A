#include "LEDController.h"

void LEDController::setup(const int led_pin) { 
    FastLED.addLeds<NEOPIXEL, 2>(leds_array, NUM_LEDS); 
}

void LEDController::update() {
    FastLED.show();
}

void LEDController::setColorUpTo(int end_led, CRGB color) {
    for (int led_index = 0; led_index < NUM_LEDS; led_index++) {
        if (led_index < end_led) {
            leds_array[led_index] = color;
        } else {
            leds_array[led_index] = CRGB::Black;
        }
    }
}

void LEDController::setColorForBallCombination(CRGB color1, CRGB color2, CRGB color3, CRGB color4, CRGB color5, CRGB color6) {
    for (int led_index = 0; led_index < NUM_LEDS; led_index++) {
        if (led_index < END_LED_1) {
            leds_array[led_index] = color1;
        } else if (led_index < END_LED_2) {
            leds_array[led_index] = color2;
        } else if (led_index < END_LED_3) {
            leds_array[led_index] = color3;
        } else if (led_index < END_LED_4) {
            leds_array[led_index] = color4;
        } else if (led_index < END_LED_5) {
            leds_array[led_index] = color5;
        } else if (led_index < END_LED_6) {
            leds_array[led_index] = color6;
        }
    }
}

void LEDController::setBrightness(int brightness) {
    FastLED.setBrightness(brightness);
}


void LEDController::cleanup() {
    // TODO: write this if required
}