// This is our main code.

#include "Arduino.h"
#include"Motor.h"
#include "Ultra.h"
#include "Bluetooth.h"
#include "Wire.h"

void setup() {

Motor.SETUP();
Ultra.SETUP();
Bluetooth.SETUP();
}

void loop() {

//Motor.forwards1();
//delay(5000);
//Motor.forwards2();
//delay(5000);
//Motor.forwards3();

//Ultra.observe();
//Ultra.dist();
//Ultra.lcd_show();

Bluetooth.read_message();

}


 // use an interrupt for overide control
