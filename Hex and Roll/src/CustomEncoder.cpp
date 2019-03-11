

//
// Encoder stuff. Pins usable (have interrupt-capability) are: 2-15, 20-23 for TeensyLC and all pins for the other Teensy's
//


// Encoder definitions and encoder variables


//------------------------------------- Main Code Below ----------------------------------------------

#include "CustomEncoder.h" 


void CustomEncoder::setup(uint16_t encoder_pinA, uint16_t encoder_pinB) {
  enc = new Encoder(encoder_pinA, encoder_pinB);
  state_changed = false;
  last_enc_pos = 0;
}


void CustomEncoder::update() {
  int32_t new_enc_pos = enc->read();
  if (new_enc_pos != last_enc_pos) {
    // update encoder position if it changed
//    Serial.print("Current Position: ");
//    Serial.println(new_enc_pos);
    last_enc_pos = new_enc_pos;
    clampEncoderPosition();
    state_changed = true;
  }
}

  int32_t CustomEncoder::getPosition() {
      return last_enc_pos;
  }


void CustomEncoder::clampEncoderPosition() {
  // clamp encoder position between MAX_ENC_POS and MIN_ENC_POS

  if (last_enc_pos > MAX_ENC_POS) {
    last_enc_pos = MAX_ENC_POS;
    enc->write(MAX_ENC_POS);
  }
  if (last_enc_pos < MIN_ENC_POS) {
    last_enc_pos = MIN_ENC_POS;
    enc->write(MIN_ENC_POS);
  }
}


void CustomEncoder::cleanup() {
  // TODO: delete all the memory allocated in setup()  
    delete enc;
}
