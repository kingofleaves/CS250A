# MUSIC250A [Project Title Here]
Final Project for Physical Interaction Design for Computer Music


## Dependencies
### Color Sensors
Download Adafruit_TCS34725 From Arduino IDE (Tools -> Manage Libraries)

Since we are using 3 hardware SDA/SCL ports on the teensy, 
  go into Adafruit_TCS34725.h:
    replace *<Wire.h>* with *<i2c_t3.h>*
    find and replace all *TwoWire* with *i2c_t3*
  go into Adafruit_TCS34725.cpp:
    find and replace all *TwoWire* with *i2c_t3*

A copy of the modified Adafruit_TCS34725.h and .cpp files are included in this repository
