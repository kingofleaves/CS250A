

//
// Encoder stuff. Pins usable (have interrupt-capability) are: 2-15, 20-23 for TeensyLC and all pins for the other Teensy's
//


// Encoder definitions and encoder variables


//------------------------------------- Main Code Below ----------------------------------------------

#include "TrackballMIDIController.h"

void TrackballMIDIController::setup(uint16_t *encoder_pins0, uint16_t *encoder_pins1, uint16_t *encoder_pins2) {
  // Set the hardware SDA, SCL ports (Wire) to the corresponding trackball units
  units[0].setup(encoder_pins0, &Wire2);
  units[0].setCC(cc[0]);
  units[1].setup(encoder_pins1, &Wire);
  units[1].setCC(cc[1]);
  units[2].setup(encoder_pins2, &Wire1);
  units[2].setCC(cc[2]);

  for (int unit_index = 0; unit_index < NUM_UNITS; unit_index++) {
    for (int ball_index = 0; ball_index < NUM_BALLS; ball_index++) {
      for (int encoder_index = 0; encoder_index < NUM_ENCODERS_PER_BALL; encoder_index++) {
        prev_data[unit_index].encoder_positions[ball_index][encoder_index] = 0;
      }
    }
    prev_data[unit_index].color_value = ColorSensor::NONE;
  }
  // Set LED brightness for all Color Sensors
  pinMode(LED_CS_PIN, OUTPUT);
  analogWrite(LED_CS_PIN, 20);
}


void TrackballMIDIController::update() {
  for (int unit_index = 0; unit_index < NUM_UNITS; unit_index++) {
    units[unit_index].update();
  }
}


void TrackballMIDIController::sendMidiMessage() {
  // map encoder counts to respective values
  // TODO: clean up this section - hasn't been updated since refactoring into class

  // Serial.println("in sendmidimessage");

  for (int unit_index = 0; unit_index < NUM_UNITS; unit_index++) {
    TrackballUnit::UnitData curr_data = units[unit_index].getData();

    for (int ball_index = 0; ball_index < NUM_BALLS; ball_index++) {
      for (int encoder_index = 0; encoder_index < NUM_ENCODERS_PER_BALL; encoder_index++) {
        int32_t curr_enc_val = curr_data.encoder_positions[ball_index][encoder_index];
        
        if (curr_enc_val == prev_data[unit_index].encoder_positions[ball_index][encoder_index]) continue;
        prev_data[unit_index].encoder_positions[ball_index][encoder_index] = curr_enc_val;

        uint8_t curr_midi_val = map(curr_enc_val, MIN_ENC_POS, MAX_ENC_POS, MIN_MIDI_VAL, MAX_MIDI_VAL);
        int curr_cc = cc[unit_index] + ball_index*2 + encoder_index;
        usbMIDI.sendControlChange(curr_cc, curr_midi_val, 0);

        // Serial.print("Encoder midi command: ");
        // Serial.print(curr_cc);
        // Serial.print(", ");
        // Serial.print(curr_midi_val);
        // Serial.print(", actual enc value: ");
        // Serial.print(curr_enc_val);
        // Serial.print(", from unit number: ");
        // Serial.print(unit_index);
        // Serial.print(", ball and encoder index: ");
        // Serial.print(ball_index);
        // Serial.print(", ");
        // Serial.println(encoder_index);    
    
      }
    }

    uint8_t color_midi_val = 127;
    uint8_t color_midi_cc = 0;
    ColorSensor::COLOR curr_color = curr_data.color_value;

    if (curr_color == prev_data[unit_index].color_value) continue;
    prev_data[unit_index].color_value = curr_color;

    if (curr_color == ColorSensor::COLOR::NONE) {
      color_midi_cc = 5;
    }
    if (curr_color == ColorSensor::COLOR::RED) {
      color_midi_cc = 6;
    }
    if (curr_color == ColorSensor::COLOR::BLUE) {
      color_midi_cc = 7;
    }
    if (curr_color == ColorSensor::COLOR::GREEN) {
      color_midi_cc = 8;
    }
    if (curr_color == ColorSensor::COLOR::YELLOW) {
      color_midi_cc = 9;
    }

    usbMIDI.sendControlChange(color_midi_cc, color_midi_val, 0);

    // Serial.print("Color midi command: ");
    // Serial.print(color_midi_cc);
    // Serial.print(", ");
    // Serial.print(color_midi_val);
    // Serial.print(", from unit number: ");
    // Serial.println(unit_index); 

    // Serial.println(curr_data.color_value);
    // Serial.print(curr_data.encoder_positions[0][0]);
    // Serial.print(", ");
    // Serial.print(curr_data.encoder_positions[0][1]);
    // Serial.print(", ");
    // Serial.print(curr_data.encoder_positions[1][0]);
    // Serial.print(", ");
    // Serial.println(curr_data.encoder_positions[1][1]);

    // usbMIDI.sendControlChange(cc[unit_index], final_value, 0);

    

  }

}

void TrackballMIDIController::cleanup() {
  // TODO: delete all the memory allocated in setup()
}
