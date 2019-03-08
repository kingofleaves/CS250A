

//
// Encoder stuff. Pins usable (have interrupt-capability) are: 2-15, 20-23 for TeensyLC and all pins for the other Teensy's
//


// Encoder definitions and encoder variables


//------------------------------------- Main Code Below ----------------------------------------------


void TrackballMIDIController::setup(uint16_t num_encoders, uint16_t *encoder_pins){
// encoder_pins should contain num_encoders * 2 elements;
  _encoder_array = new Encoder*[num_encoders];
  _encoder_positions = new uint32_t[num_encoders];
  for (int encoder_index = 0; encoder_index < num_encoders; encoder_index++) {
    _encoderArray[encoder_index] = new Encoder(encoder_pins[encoder_index*2, encoder_index*2 + 1]);
    _encoder_positions[encoder_index] = 0;
  }
  _num_encoders = num_encoders;
}


void TrackballMIDIController::update() {
  updateAllColorValues();
  updateAllEncoders();
}


void TrackballMIDIController::sendMidiMessage() {
  // map encoder counts to respective values
// TODO: clean up this section - hasn't been updated since refactoring into class
  
  int instr_vert_val = map(instr_enc_vert_pos, MIN_ENC_POS, MAX_ENC_POS, MIN_INSTR_VAL, MAX_INSTR_VAL);
  int instr_horz_val = map(instr_enc_horz_pos, MIN_ENC_POS, MAX_ENC_POS, MIN_INSTR_VAL, MAX_INSTR_VAL);
  int effect_vert_val = map(effect_enc_vert_pos, MIN_ENC_POS, MAX_ENC_POS, MIN_EFFECT_VAL, MAX_EFFECT_VAL);
  int effect_horz_val = map(effect_enc_horz_pos, MIN_ENC_POS, MAX_ENC_POS, MIN_EFFECT_VAL, MAX_EFFECT_VAL);

  // TODO: use these values to do something.

//  Serial.print("instrument control - Vertical: ");
//  Serial.println(instr_vert_val);
//  Serial.print("instrument control - Horizontal: ");
//  Serial.println(instr_horz_val);
//  Serial.print("effect control - Vertical: ");
//  Serial.println(effect_vert_val);
//  Serial.print("effect control - Horizontal: ");
//  Serial.println(effect_horz_val);

//  usbMIDI.sendControlChange(control, value, channel);

}


void TrackballMIDIController::updateAllEncoders(){

  for (uint16_t encoder_index = 0; encoder_index < _num_encoders; encoder_index++) {
    updateEncoderPosition(encoder_index);
  }
}


void TrackballMIDIController::updateAllColorValues() {

  for (uint16_t color_sensor_index = 0; color_sensor_index < _num_color_sensors; color_sensor_index++) {
    updateColorValue(color_sensor_index);
  }
}


void TrackballMIDIController::updateColorValue(uint16_t color_sensor_index) {
// Updates color_values array with new data from the specified color sensor.

  curr_color_value_loc = _color_values + color_sensor_index * 4;
  _color_sensor_array[color_sensor_index]->getRawData(
    curr_color_value_loc, 
    curr_color_value_loc+1, 
    curr_color_value_loc+2, 
    curr_color_value_loc+3);

}


void TrackballMIDIController::updateEncoderPosition(uint16_t encoder_index) {
// Updates the enc_pos variable with current encoder position.

  uint32_t new_enc_pos = _encoder_array[encoder_index]->read();
  if (new_enc_pos != _encoder_positions[encoder_index]) {
    // update encoder position if it changed
    Serial.print("Current Position: ");
    Serial.println(new_enc_pos);
    _encoder_positions[encoder_index] = new_enc_pos;
    clampEncoderPosition(encoder_index);
  }
  
}


void TrackballMIDIController::clampEncoderPosition(uint16_t encoder_index) {
// clamp encoder position between MAX_ENC_POS and MIN_ENC_POS

  if (_encoder_positions[encoder_index] > MAX_ENC_POS){
      _encoder_positions[encoder_index] = MAX_ENC_POS;
      _encoder_array[encoder_index]->write(MAX_ENC_POS);
  }
  if (_encoder_positions[encoder_index] < MIN_ENC_POS){
      _encoder_positions[encoder_index] = MIN_ENC_POS;
      _encoder_array[encoder_index]->write(MIN_ENC_POS);
  }
}


void TrackballMIDIController::cleanup(){
  // TODO: delete all the memory allocated in setup()
  
}