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
            int grad_start = END_LED_1;
            int grad_end = END_LED_2;
            uint16_t temp_R = color1.r+((float)(led_index-grad_start)/(grad_end-grad_start))*(color3.r-color1.r);
            uint16_t temp_G = color1.g+((float)(led_index-grad_start)/(grad_end-grad_start))*(color3.g-color1.g);
            uint16_t temp_B = color1.b+((float)(led_index-grad_start)/(grad_end-grad_start))*(color3.b-color1.b);
            color2 = CRGB(temp_R,temp_G,temp_B);
            leds_array[led_index] = color2;
        } else if (led_index < END_LED_3) {
            leds_array[led_index] = color3;
        } else if (led_index < END_LED_4) {
            int grad_start = END_LED_3;
            int grad_end = END_LED_4;
            uint16_t temp_R = color3.r+((float)(led_index-grad_start)/(grad_end-grad_start))*(color5.r-color3.r);
            uint16_t temp_G = color3.g+((float)(led_index-grad_start)/(grad_end-grad_start))*(color5.g-color3.g);
            uint16_t temp_B = color3.b+((float)(led_index-grad_start)/(grad_end-grad_start))*(color5.b-color3.b);
            color4 = CRGB(temp_R,temp_G,temp_B);
            leds_array[led_index] = color4;
        } else if (led_index < END_LED_5) {
            leds_array[led_index] = color5;
        } else if (led_index < END_LED_6) {
            int grad_start = END_LED_5;
            int grad_end = END_LED_6;
            uint16_t temp_R = color5.r+((float)(led_index-grad_start)/(grad_end-grad_start))*(color1.r-color5.r);
            uint16_t temp_G = color5.g+((float)(led_index-grad_start)/(grad_end-grad_start))*(color1.g-color5.g);
            uint16_t temp_B = color5.b+((float)(led_index-grad_start)/(grad_end-grad_start))*(color1.b-color5.b);
            color6 = CRGB(temp_R,temp_G,temp_B);
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