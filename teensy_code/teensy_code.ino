#include "TrackballMIDIController.h"

TrackballMIDIController controller;

static const uint16_t num_encoders = 2;
uint16_t encoder_pin_array[num_encoders * 2] = {29,30,31,32};

void setup() {
  Serial.begin(9600);
  controller.setup(num_encoders, encoder_pin_array);
}

void loop() {
  controller.update();
  controller.sendMidiMessage();
}
