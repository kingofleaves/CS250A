#include "LEDController.h"

void LEDController::setup() { 
    for (int module_index = 0; module_index < NUM_MODULES; module_index++) {
        FastLED.addLeds<NEOPIXEL, 33>(leds_array[module_index], NUM_LEDS); 
    }
}

void LEDController::update() {
    FastLED.show();
}

void LEDController::setColorAllModules(CRGB color) {
    for (int module_index = 0; module_index < NUM_MODULES; module_index++) {
        setColorOneModule(module_index, color); 
    }
}


void LEDController::setColorOneModule(int module_index, CRGB color) {
    for (int led_index = 0; led_index < NUM_LEDS; led_index++) {
    leds_array[module_index][led_index] = color;
    }
}

void LEDController::setColorForBallCombination(CRGB color1, CRGB color2, CRGB color3) {
    
}

void LEDController::cleanup() {
    // TODO: write this if required
}