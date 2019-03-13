#ifndef _TRACKBALL_MIDI_CONTROLLER_H
#define _TRACKBALL_MIDI_CONTROLLER_H

#include "TrackballUnit.h"

#define NUM_UNITS 3

// pin definitions
#define LED_CS_PIN 30

// min and max values for scaled instrument and effect values (after mapping from encoder raw counts)
#define MIN_MIDI_VAL 0
#define MAX_MIDI_VAL 127

class TrackballMIDIController {
public:
  
  TrackballMIDIController(){};
  ~TrackballMIDIController(){cleanup();};

  void setup(uint16_t *encoder_pins0, uint16_t *encoder_pins1, uint16_t *encoder_pins2); 
  void update();
  void sendMidiMessage();
  TrackballUnit::UnitData *getData();


private:

  TrackballUnit units[NUM_UNITS];

  TrackballUnit::UnitData prev_data[NUM_UNITS];

  uint8_t cc[NUM_UNITS] = {10, 20, 30};
  
  void cleanup();
};

#endif // TRACKBALL_MIDI_CONTROLLER_H
