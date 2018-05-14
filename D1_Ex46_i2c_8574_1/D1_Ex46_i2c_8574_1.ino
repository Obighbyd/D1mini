//_____D1_Ex46_i2c_8574_1.ino_________________170114-180514_____
// Connect a PCF8574 I2C-8bit-IO-Expander (or PCF8575 I2C-16bit-
// IO-Expander) to a D1mini (7bit-address 0x20). 
// Alternate flashing of IO-pins with 1Hz.
// Hardware: WeMos D1 Mini
//           PCF8574 (or PCF8575) @ i2c (SCL=D1, SDA=D2)
// Created by Karl Hartinger, January 14, 2017
// Last modified: May 14, 2018.
// Released into the public domain.
#include <Wire.h>
#define DEBUG 1
#define PCF8574_ADDR (0x20)       // address of PCF8574

void setup() {
 if(DEBUG) { Serial.begin(115200); Serial.println(); }
 Wire.begin();
}

void loop() {
 Wire.beginTransmission(PCF8574_ADDR);
 Wire.write(0xAA);
 Wire.write(0xAA);                // remove line if PCF8574
 Wire.endTransmission();
 delay(500);
 Wire.beginTransmission(PCF8574_ADDR);
 Wire.write(0x55);
 Wire.write(0x55);                // remove line if PCF8574
 Wire.endTransmission();
 delay(500);
}

