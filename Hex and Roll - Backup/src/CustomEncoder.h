#ifndef _CUSTOM_ENCODER_H
#define _CUSTOM_ENCODER_H

#include <Encoder.h>
#include "Adafruit_TCS34725.h"

// Encoder max and min values (2 counts per detent, 30 detents => 60 counts per revolution
#define MAX_ENC_POS 31
#define MIN_ENC_POS -31

class CustomEncoder {
public:
  
  CustomEncoder(){};
  ~CustomEncoder(){cleanup();};

  Encoder *enc;
  void setup(uint16_t encoder_pinA, uint16_t encoder_pinB);  // encoder_pins should contain num_encoders * 2 elements;
  bool update();
  int32_t getPosition();

private:

  bool state_changed;
  int32_t last_enc_pos;

  void clampEncoderPosition();
  void cleanup();
};

#endif // _CUSTOM_ENCODER_H
