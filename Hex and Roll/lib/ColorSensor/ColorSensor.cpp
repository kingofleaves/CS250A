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
        temp = tcs->calculateColorTemperature(r,g,b);
        // Serial.print("r: ");
        // Serial.print(r);
        // Serial.print(", g: ");
        // Serial.print(g);
        // Serial.print(", b: ");
        // Serial.print(b);
        // Serial.print(", c: ");
        // Serial.print(c);
        // Serial.print(", Temp: ");
        // Serial.print(temp);
        // Serial.println();
                

        if (temp < 3800) {
            current_color = YELLOW;
        }
        else if (temp<5600&&temp>4000) {
            current_color = RED;
        }
        else if (temp<6900&&temp>5600) {
            current_color = GREEN;
        }
        else if (temp>7000) {
            current_color = BLUE;
        }
        else {
            current_color = current_color;
        }

    }

    void ColorSensor::cleanup() {
        delete tcs;
    }