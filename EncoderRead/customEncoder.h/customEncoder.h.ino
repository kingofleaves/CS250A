// Our Encoder Class with stored variables

void updateEncoderPosition(Encoder curr_encoder, long &curr_enc_pos) {
//
// Updates the enc_pos variable with current encoder position.
  long new_enc_pos = curr_encoder.read();
  if (new_enc_pos != curr_enc_pos) {
    // update encoder position if it changed
    Serial.print("Current Position: ");
    Serial.println(new_enc_pos);
    enc_pos = new_enc_pos;
    clampEncoderPosition();
  }
  
}

void clampEncoderPosition(Encoder curr_encoder, long &curr_enc_pos) {
//
// clamp encoder position
//
  if (enc_pos > MAX_ENC_POS){
      enc_pos = MAX_ENC_POS;
      setEncoder(MAX_ENC_POS);
  }
  if (enc_pos < MIN_ENC_POS){
      enc_pos = MIN_ENC_POS;
      setEncoder(MIN_ENC_POS);
  }
}

void setEncoder(Encoder curr_encoder, long new_pos) {
//
// reset encoder to the new specified position
//
  curr_encoder.write(new_pos);
}
