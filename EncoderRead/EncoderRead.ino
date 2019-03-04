#include <Encoder.h>

//
// Encoder stuff. Pins usable (have interrupt-capability) are: 2-15, 20-23
//

// Encoders for trackball controlling instrument
#define PIN_INSTR_VERT_A 20
#define PIN_INSTR_VERT_B 21
#define PIN_INSTR_HORZ_A 22
#define PIN_INSTR_HORZ_B 23

// Encoders for trackball controlling effect
#define PIN_EFFECT_VERT_A 12
#define PIN_EFFECT_VERT_B 13
#define PIN_EFFECT_HORZ_A 14
#define PIN_EFFECT_HORZ_B 15

// Encoder max and min values (2 counts per detent, 30 detents => 60 counts per revolution
#define MAX_ENC_POS 180
#define MIN_ENC_POS -180

// min and max values for scaled instrument and effect values (after mapping from encoder raw counts)
#define MIN_INSTR_VAL -180
#define MAX_INSTR_VAL 180
#define MIN_EFFECT_VAL -180
#define MAX_EFFECT_VAL 180

// Encoder definitions and encoder variables
Encoder instrVertEnc(PIN_INSTR_VERT_A, PIN_INSTR_VERT_B);
long instr_enc_vert_pos = 0;
Encoder instrHorzEnc(PIN_INSTR_HORZ_A, PIN_INSTR_HORZ_B);
long instr_enc_horz_pos = 0;
Encoder effectVertEnc(PIN_EFFECT_VERT_A, PIN_EFFECT_VERT_B);
long effect_enc_vert_pos = 0;
Encoder effectHorzEnc(PIN_EFFECT_HORZ_A, PIN_EFFECT_HORZ_B);
long effect_enc_horz_pos = 0;

//------------------------------------- Main Code Below ----------------------------------------------

void setup() {
  // put your setup code here, to run once:
 
}

void loop() {
  // put your main code here, to run repeatedly:
  updateAllEncoders();
  sendMidiMessage();
}

void sendMidiMessage() {
  // map encoder counts to respective values
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

}

void updateAllEncoders(){
  updateEncoderPosition(instrVertEnc, instr_enc_vert_pos);
  updateEncoderPosition(instrHorzEnc, instr_enc_horz_pos);
  updateEncoderPosition(effectVertEnc, effect_enc_vert_pos);
  updateEncoderPosition(effectHorzEnc, effect_enc_horz_pos);
}

void updateEncoderPosition(Encoder curr_encoder, long &curr_enc_pos) {
//
// Updates the enc_pos variable with current encoder position.
  long new_enc_pos = curr_encoder.read();
  if (new_enc_pos != curr_enc_pos) {
    // update encoder position if it changed
    Serial.print("Current Position: ");
    Serial.println(new_enc_pos);
    curr_enc_pos = new_enc_pos;
    clampEncoderPosition(curr_encoder, curr_enc_pos);
  }
  
}

void clampEncoderPosition(Encoder curr_encoder, long &curr_enc_pos) {
//
// clamp encoder position
//
  if (curr_enc_pos > MAX_ENC_POS){
      curr_enc_pos = MAX_ENC_POS;
      setEncoder(curr_encoder, MAX_ENC_POS);
  }
  if (curr_enc_pos < MIN_ENC_POS){
      curr_enc_pos = MIN_ENC_POS;
      setEncoder(curr_encoder, MIN_ENC_POS);
  }
}

void setEncoder(Encoder curr_encoder, long new_pos) {
//
// reset encoder to the new specified position
//
  curr_encoder.write(new_pos);
}
