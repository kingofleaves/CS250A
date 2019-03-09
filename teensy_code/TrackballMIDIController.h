#include <Wire.h>
#include <Encoder.h>
#include "Adafruit_TCS34725.h"

#ifndef _TRACKBALL_MIDI_CONTROLLER_H
#define _TRACKBALL_MIDI_CONTROLLER_H

// Encoder max and min values (2 counts per detent, 30 detents => 60 counts per revolution
#define MAX_ENC_POS 180
#define MIN_ENC_POS -180

// min and max values for scaled instrument and effect values (after mapping from encoder raw counts)
#define MIN_INSTR_VAL 0
#define MAX_INSTR_VAL 127
#define MIN_EFFECT_VAL 0
#define MAX_EFFECT_VAL 127

class TrackballMIDIController {
public:

  uint16_t _num_encoders;
  Encoder **_encoder_array;
  int32_t *_encoder_positions;

  uint16_t _num_color_sensors;
  Adafruit_TCS34725 **_color_sensor_array;
  uint16_t *_color_values;
  
  TrackballMIDIController(){};
  ~TrackballMIDIController(){cleanup();};

  void setup(uint16_t num_encoders, uint16_t *encoder_pins);  // encoder_pins should contain num_encoders * 2 elements;
  void update();
  void sendMidiMessage();


private:

  bool state_changed;
  uint16_t sal_cc;
  uint16_t austen_cc;
  uint16_t ye_cc;

  void updateAllColorValues();
  void updateAllEncoders();
  void updateColorValue(uint16_t color_sensor_index);
  void updateEncoderPosition(uint16_t encoder_index);
  void clampEncoderPosition(uint16_t encoder_index);
  void cleanup();
};

#endif // TRACKBALL_MIDI_CONTROLLER_H
