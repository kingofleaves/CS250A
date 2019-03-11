

//
// Encoder stuff. Pins usable (have interrupt-capability) are: 2-15, 20-23 for TeensyLC and all pins for the other Teensy's
//


// Encoder definitions and encoder variables


//------------------------------------- Main Code Below ----------------------------------------------

#include "TrackballMIDIController.h"


  void TrackballMIDIController::setup(uint16_t *encoder_pins0, uint16_t *encoder_pins1, uint16_t *encoder_pins2) {
  units[0].setup(encoder_pins0);
  units[1].setup(encoder_pins1);
  units[2].setup(encoder_pins2);
  
  cc[0] = AUSTEN_CC;
  cc[0] = SAL_CC;
  cc[0] = YE_CC;
}


void TrackballMIDIController::update() {
  for (int unit_index = 0; unit_index < NUM_UNITS; unit_index++) {
    units[unit_index].update();
  }
}


void TrackballMIDIController::sendMidiMessage() {
  // map encoder counts to respective values
  // TODO: clean up this section - hasn't been updated since refactoring into class

  Serial.println("in sendmidimessage");

  for (int unit_index = 0; unit_index < NUM_UNITS; unit_index++) {
    TrackballUnit::UnitData curr_data = units[unit_index].getData();
    int32_t final_value = curr_data.encoder_positions[0][0] + curr_data.encoder_positions[0][1] + curr_data.encoder_positions[1][0] + curr_data.encoder_positions[1][1];
    usbMIDI.sendControlChange(cc[unit_index], final_value, 0);
    // Serial.print(curr_data.encoder_positions[0][0]);
    // Serial.print(", ");
    // Serial.print(curr_data.encoder_positions[0][1]);
    // Serial.print(", ");
    // Serial.print(curr_data.encoder_positions[1][0]);
    // Serial.print(", ");
    // Serial.println(curr_data.encoder_positions[1][1]);
    
  }

}

void TrackballMIDIController::cleanup() {
  // TODO: delete all the memory allocated in setup()
}
