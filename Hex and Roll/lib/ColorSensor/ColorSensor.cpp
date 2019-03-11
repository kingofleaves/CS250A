    #include "ColorSensor.h"
    
    ColorSensor::COLOR ColorSensor::getColor() {
        return current_color;
    }

    void ColorSensor::setup(i2c_t3 *theWire) {
        _wire = theWire;
        if (tcs != NULL) delete tcs; // memory management
        tcs = new Adafruit_TCS34725(_int_time, _gain);
        tcs->begin(TCS34725_ADDRESS, _wire);
    }

    void ColorSensor::setup(tcs34725IntegrationTime_t int_time, tcs34725Gain_t gain, i2c_t3 *theWire) {
        _int_time = int_time;
        _gain = gain;
        _wire = theWire;
        if (tcs != NULL) delete tcs; // memory management
        tcs = new Adafruit_TCS34725(_int_time, _gain);
        tcs->begin(TCS34725_ADDRESS, _wire);
    }


    void ColorSensor::update() {
        tcs->getRawData(&r, &g, &b, &c);

        // Serial.print("r: ");
        // Serial.print(r);
        // Serial.print(", g: ");
        // Serial.print(g);
        // Serial.print(". b: ");
        // Serial.print(b);
        // Serial.print("c: ");
        // Serial.print(c);
        // Serial.println();
                

        if (c > 600) {
            current_color = NONE;
        }
        else if (g > pow(threshold_multiplier, 2)*r && g > threshold_multiplier*b) {
            current_color = GREEN;
        }
        else if (r > g && r > threshold_multiplier*b && g > threshold_multiplier*b) {
            current_color = YELLOW;
        }
        else if (b > pow(threshold_multiplier, 2)*r) {
            current_color = BLUE;
        }
        else {
            current_color = RED;
        }

    }

    void ColorSensor::cleanup() {
        delete tcs;
    }