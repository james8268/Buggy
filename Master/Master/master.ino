// This is the main code.          // taken baud rates:9600(bluetooth), 4800 (Ultrasound)

#include "Arduino.h"
#include"Motor.h"
#include "Ultra.h"
#include "Bluetooth.h"
#include "Wire.h"
#include "operation.h"

void setup() {

Motor.SETUP();
Ultra.SETUP();
Bluetooth.SETUP();
operation.SETUP();

}

void loop() {

Bluetooth.read_message();  

operation.level();
operation.noComs();

}



 // use an interrupt for overide control
