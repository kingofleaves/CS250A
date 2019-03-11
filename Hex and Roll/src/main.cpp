#include "TrackballMIDIController.h"

TrackballMIDIController controller;

uint16_t encoder_pin_array0[4] = {11,12,13,14};
uint16_t encoder_pin_array1[4] = {29,30,31,32};
uint16_t encoder_pin_array2[4] = {20,21,22,23};

void setup() {
  // Serial.begin(9600);
  controller.setup(encoder_pin_array0, encoder_pin_array1, encoder_pin_array2);
}

void loop() {
  controller.update();
  controller.sendMidiMessage();
}