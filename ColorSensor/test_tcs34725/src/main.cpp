#include "ColorSensor.h"

ColorSensor cs;

void setup() {
  Serial.begin(9600);
  cs.setup(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X, &Wire1);
  
  pinMode(23, OUTPUT);
  analogWrite(23,10); // LED brightness for color sensor
}

void loop() {
  cs.update();
  Serial.println(cs.getColor());
}

// #include <Wire.h>
// #include "Adafruit_TCS34725softi2c.h"
// #include "Adafruit_TCS34725.h"

// /* Example code for the Adafruit TCS34725 breakout library */

// /* Connect SCL    to analog 5
//    Connect SDA    to analog 4
//    Connect VDD    to 3.3V DC
//    Connect GROUND to common ground */

// /* Initialise with default values (int time = 2.4ms, gain = 1x) */

// /* Initialise with specific int time and gain values */
// #define SDA0 16
// #define SCL0 17
// #define SDA1 11
// #define SCL1 12

// // Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

// Adafruit_TCS34725softi2c tcs = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X, SDA0, SCL0);
// // Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X, SDA1, SCL1);

// enum MODES {RED, BLUE, GREEN, YELLOW, NONE};
// int mode = RED;
// uint16_t r, g, b, c, colorTemp, lux, prevTemp, prevLux;

// void setup(void) {
//   Serial.begin(9600);
  

//   if (tcs.begin()) {
//     Serial.println("Found sensor");
//   } else {
//     Serial.println("No TCS34725 found ... check your connections");
//     while (1);
//   }
//   pinMode(23, OUTPUT);
//   analogWrite(23,10);

//   // Now we're ready to get readings!
// }

// void loop(void) {


//   tcs.getRawData(&r, &g, &b, &c);
//   colorTemp = tcs.calculateColorTemperature(r, g, b);
//   lux = tcs.calculateLux(r, g, b);
  
//   Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
//   Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
//   Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
//   Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
//   Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
//   Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
//   Serial.println(" ");
//   Serial.println(prevLux);
//   Serial.println(prevTemp);

//   if (c > 600) {
//     mode = NONE;
//   }
//   else if (g > 1.25*r && g > 1.1*b) {
//     mode = GREEN;
//   }
//   else if (r > g && r > 1.15*b && g > 1.15*b) {
//     mode = YELLOW;
//   }
//   else if (b > 1.2*r) {
//     mode = BLUE;
//   }
//   else {
//     mode = RED;
//   }
  
  

// //  if((prevLux>1.1*lux||prevLux<0.9*lux)||(prevTemp>1.1*colorTemp||prevTemp<0.9*colorTemp)) {
// //     Serial.println("Change Detected");
// //     if (mode == NONE) {
// //       if(colorTemp>4000&&colorTemp<5600) {
// //         mode = RED;
// //       }
// //       else if(colorTemp>5600&&colorTemp<6100) {
// //         mode = GREEN;
// //       }
// //       else if(colorTemp>6100&&colorTemp<6700) {
// //         mode = BLUE;
// //       }
// //       else if(colorTemp>3400&&colorTemp<4000) {
// //         mode = YELLOW;
// //       }
// //       else {
// //         mode=NONE;
// //       }
// //     } else {
// //       mode=NONE;
// //     }   
    
// //  }
// //   prevLux = lux;
// //   prevTemp = colorTemp;


//   switch(mode) {
//     case RED:
//     Serial.println("RED Mode");
//     break;
//     case GREEN:
//     Serial.println("GREEN Mode");
//     break;
//     case BLUE:
//     Serial.println("BLUE Mode");
//     break;
//     case YELLOW:
//     Serial.println("YELLOW Mode");
//     break;
//     default:
//     Serial.println("NO Mode");
//     break;
//   }

// }
