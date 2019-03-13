#include "TrackballMIDIController.h"
#include "LEDController.h"

#define LED_BG_PIN 2
#define LED_BG_PIN2 0

TrackballMIDIController controller;
LEDController leds;

unsigned long curTime = 0;
unsigned long lastMidi = 0;
unsigned long midiTimer = 0;

uint16_t encoder_pin_array0[8] = {9,10,11,12, 14,15,16,17};
uint16_t encoder_pin_array1[8] = {20,21,22,23, 33,34,35,36};
uint16_t encoder_pin_array2[8] = {24,25,26,27, 5,6,7,8};

// Function Prototypes
void setLedsToBalls();


void setup() {
  // Serial.begin(9600);
  controller.setup(encoder_pin_array0, encoder_pin_array1, encoder_pin_array2);
  leds.setup(LED_BG_PIN,LED_BG_PIN2);
}

void loop() {
  curTime=millis();
  // Serial.println("-----------------------------------------");
  controller.update();
  // delay(1000);
  int pulse = map(curTime % 469,0,468,0,100);
  leds.setBrightness(200-pulse);

  if(curTime>midiTimer+lastMidi) {
    controller.sendMidiMessage();
    lastMidi = curTime;
  }

  setLedsToBalls();
}

void setLedsToBalls() {
  TrackballUnit::UnitData *data = controller.getData();
  CRGB color_array[NUM_UNITS * NUM_BALLS];
  uint8_t positions[NUM_UNITS * NUM_BALLS][NUM_ENCODERS_PER_BALL];
  for (int unit_index = 0; unit_index < NUM_UNITS; unit_index++) {
    for (int ball_index = 0; ball_index < NUM_BALLS; ball_index++) {
      for (int enc_index = 0; enc_index < NUM_ENCODERS_PER_BALL; enc_index++) {
        int32_t enc_pos = data[unit_index].encoder_positions[ball_index][enc_index];
        uint8_t indicator_pos = map(enc_pos, MIN_ENC_POS, MAX_ENC_POS, leds.end_led2_array[unit_index*2 + ball_index],  leds.end_led2_array[unit_index*2 + ball_index+1]);
        positions[unit_index*NUM_BALLS + ball_index][enc_index] = indicator_pos;
      }
    }

    CRGB curr_color; 
    switch (data[unit_index].color_value) {
      case ColorSensor::NONE : 
        curr_color = CRGB::White;
        break;
      
      case ColorSensor::RED : 
        curr_color = CRGB::Red;
        break;
      
      case ColorSensor::BLUE : 
        curr_color = CRGB::Blue;
        break;
        
      case ColorSensor::GREEN : 
        curr_color = CRGB::Green;
        break;
      
      case ColorSensor::YELLOW : 
        curr_color = CRGB::Yellow;
        break;
    }
    color_array[unit_index*2] = curr_color;
  }
  for (int unit_index = 0; unit_index < NUM_UNITS; unit_index++) {
    color_array[unit_index*2+1] = color_array[unit_index*2]/2 + color_array[(unit_index*2+2)%6]/2;
  }
  // The for loop above does the following 3 lines: 
  // color_array[1] = color_array[0]/2 + color_array[2]/2;
  // color_array[3] = color_array[0]/2 + color_array[2]/2;
  // color_array[5] = color_array[4]/2 + color_array[0]/2;

  leds.setColorForBallCombination(color_array[0], color_array[5], color_array[4], color_array[3], color_array[2], color_array[1]);
  // leds.setColorIndicators(color_array, positions);
  
  // leds.setInnerColor(color_array[0],color_array[2],color_array[1], 
  //   data[0].encoder_positions[0], 
  //   data[0].encoder_positions[1], 
  //   data[1].encoder_positions[0], 
  //   data[1].encoder_positions[1],     
  //   data[2].encoder_positions[0], 
  //   data[2].encoder_positions[1]);
  
  // leds.setColorUpTo(156,CRGB(230,128,10));
  

  leds.update();
}