#ifndef _TRACKBALL_MIDI_CONTROLLER_H
#define _TRACKBALL_MIDI_CONTROLLER_H

#include "TrackballUnit.h"

#define NUM_UNITS 3

// min and max values for scaled instrument and effect values (after mapping from encoder raw counts)
#define MIN_INSTR_VAL 0
#define MAX_INSTR_VAL 127
#define MIN_EFFECT_VAL 0
#define MAX_EFFECT_VAL 127

// CC definitions
#define AUSTEN_CC 25
#define SAL_CC 26
#define YE_CC 27

class TrackballMIDIController {
public:
  
  TrackballMIDIController(){};
  ~TrackballMIDIController(){cleanup();};

  void setup(uint16_t *encoder_pins0, uint16_t *encoder_pins1, uint16_t *encoder_pins2); 
  void update();
  void sendMidiMessage();


private:

  TrackballUnit units[NUM_UNITS];

  uint16_t cc[NUM_UNITS] = {25, 26, 27};
  
  void cleanup();
};

#endif // TRACKBALL_MIDI_CONTROLLER_H
