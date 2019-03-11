#ifndef _TRACKBALL_UNIT_H
#define _TRACKBALL_UNIT_H

#include "CustomEncoder.h"
#include "ColorSensor.h"

#define NUM_ENCODERS_PER_BALL 2
#define NUM_BALLS 2
#define NUM_ENCODERS 4

class TrackballUnit {
public:

  struct UnitData {
      int32_t encoder_positions[NUM_BALLS][NUM_ENCODERS_PER_BALL]; // first ball is instrument, second ball is effect
      ColorSensor::COLOR color_value;
  };

  TrackballUnit(){};
  ~TrackballUnit(){cleanup();};

  void setup(uint16_t *encoder_pins, i2c_t3 *theWire);  // encoder_pins should contain 2 balls * 2 enc/ball * 2 pins/enc = 8 elements;
  void update();
  UnitData getData();
  uint16_t getCC();


private:

  CustomEncoder encoder_array[2][2];
  ColorSensor cs;

  UnitData last_data;
  uint16_t cc_midi;

  void updateAllEncoders();
  void getColor();
  void cleanup();
};

#endif // TRACKBALL_MIDI_CONTROLLER_H
