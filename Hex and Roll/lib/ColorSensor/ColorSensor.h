#ifndef _COLOR_SENSOR_H
#define _COLOR_SENSOR_H

#include "Adafruit_TCS34725.h"

class ColorSensor {
public:

    enum COLOR {RED, BLUE, GREEN, YELLOW, NONE};

    ColorSensor(){
        current_color = NONE;
        threshold_multiplier = 1.1;
    };
    ~ColorSensor(){cleanup();};

    COLOR getColor();
    void setup(i2c_t3 *theWire);
    void setup(tcs34725IntegrationTime_t int_time, tcs34725Gain_t gain, i2c_t3 *theWire);
    void update();

    void setThresholdMultiplier(int multiplier);

private:
    Adafruit_TCS34725 *tcs;
    tcs34725IntegrationTime_t _int_time = TCS34725_INTEGRATIONTIME_24MS;
    tcs34725Gain_t _gain = TCS34725_GAIN_16X;
    i2c_t3 *_wire;
    uint16_t r, g, b, c;
    COLOR current_color;
    int threshold_multiplier;

    void cleanup();
};





#endif // _COLOR_SENSOR_H
