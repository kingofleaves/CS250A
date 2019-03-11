#include "TrackballMIDIController.h"
#include "LEDController.h"

#define LED_BG_PIN 2

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
  leds.setup(LED_BG_PIN);
}

void loop() {
  curTime=millis();
  controller.update();
  if(curTime>midiTimer+lastMidi) {
    controller.sendMidiMessage();
    lastMidi = curTime;
  }

  setLedsToBalls();
}

void setLedsToBalls() {
  TrackballUnit::UnitData *data = controller.getData();
  CRGB color_array[NUM_UNITS];
  for (int unit_index = 0; unit_index < NUM_UNITS; unit_index++) {
    switch (data[unit_index].color_value) {
      case ColorSensor::NONE : 
        color_array[unit_index] = CRGB::White;
        break;
      
      case ColorSensor::RED : 
        color_array[unit_index] = CRGB::Red;
        break;
      
      case ColorSensor::BLUE : 
        color_array[unit_index] = CRGB::Blue;
        break;
        
      case ColorSensor::GREEN : 
        color_array[unit_index] = CRGB::Green;
        break;
      
      case ColorSensor::YELLOW : 
        color_array[unit_index] = CRGB::Yellow;
        break;
    }
  }
  leds.setColorForBallCombination(color_array[0], CRGB(230,128,10), color_array[2], CRGB(230,128,10), color_array[1], CRGB(230,128,10));
  // leds.setColorUpTo(156,CRGB(230,128,10));
  
  leds.setBrightness(50);
  leds.update();
}