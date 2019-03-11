#include "TrackballMIDIController.h"
#include "LEDController.h"

#define LED_BG_PIN 2

TrackballMIDIController controller;
LEDController leds;

unsigned long curTime = 0;
unsigned long lastMidi = 0;
unsigned long midiTimer = 300;

uint16_t encoder_pin_array0[8] = {9,10,11,12, 14,15,16,17};
uint16_t encoder_pin_array1[8] = {20,21,22,23, 33,34,35,36};
uint16_t encoder_pin_array2[8] = {24,25,26,27, 5,6,7,8};

void setup() {
  // Serial.begin(9600);
  controller.setup(encoder_pin_array0, encoder_pin_array1, encoder_pin_array2);
  leds.setup(LED_BG_PIN);
}

void loop() {
  curTime=millis();
  controller.update();
  if(curTime>midiTimer+lastMidi) {
    controller.sendMidiMessage();
    lastMidi = curTime;
  }
  leds.setColorUpTo(156, CRGB::Red);
  leds.setBrightness(10);
  leds.update();
}