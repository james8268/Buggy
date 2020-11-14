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
Serial.begin(9600);

}

void loop() {

Bluetooth.read_message();  



}


 // use an interrupt for overide control
