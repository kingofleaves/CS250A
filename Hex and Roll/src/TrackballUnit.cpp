

//
// Encoder stuff. Pins usable (have interrupt-capability) are: 2-15, 20-23 for TeensyLC and all pins for the other Teensy's
//


// Encoder definitions and encoder variables


//------------------------------------- Main Code Below ----------------------------------------------

#include "TrackballUnit.h"


void TrackballUnit::setup(uint16_t *encoder_pins) {
    // encoder_pins should contain num_encoders * 2 elements;
    for (int ball_index = 0; ball_index < NUM_BALLS; ball_index++) {
        for (int encoder_index = 0; encoder_index < NUM_ENCODERS_PER_BALL; encoder_index++) {
            int encoder_first_pin_pos = (ball_index * NUM_ENCODERS_PER_BALL + encoder_index) *2;
            encoder_array[ball_index][encoder_index].setup(encoder_pins[encoder_first_pin_pos], encoder_pins[encoder_first_pin_pos + 1]);
        }
    }

    // Initialize class variables
    for (int ball_index = 0; ball_index < NUM_BALLS; ball_index++) {
        for (int encoder_index = 0; encoder_index < NUM_ENCODERS_PER_BALL; encoder_index++) {
            last_data.encoder_positions[ball_index][encoder_index] = 0;
        }
    }
    last_data.color_value = ColorSensor::NONE;

    cc_midi = 0;
}


void TrackballUnit::update() {
  updateAllEncoders();
  getColor();
}

TrackballUnit::UnitData TrackballUnit::getData() {
    return last_data;
}

uint16_t TrackballUnit::getCC() {
    return cc_midi;
}

void TrackballUnit::updateAllEncoders() {

    for (int ball_index = 0; ball_index < NUM_BALLS; ball_index++) {
        for (int encoder_index = 0; encoder_index < NUM_ENCODERS_PER_BALL; encoder_index++) {
            encoder_array[ball_index][encoder_index].update();
            last_data.encoder_positions[ball_index][encoder_index] = encoder_array[ball_index][encoder_index].getPosition();
        }
    }
}


void TrackballUnit::getColor() {
    last_data.color_value = cs.getColor();
}

void TrackballUnit::cleanup() {
  // TODO: delete all the memory allocated in setup()

}
