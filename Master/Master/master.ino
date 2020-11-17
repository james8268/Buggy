// This is the main code, It is uploaded to the Arduino Mega. It contains the setup functions for specific libraries. 

// taken baud rates:9600(bluetooth), 4800 (Ultrasound)

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

Bluetooth.read_message();   // this reads messages sent over WiFi or Bluetooth to the esp32 and actions them. 

operation.level();  // this function will stop the buggy if the tilt sensor is triggered, a buzzer and warning message will alert the user. 
operation.noComs();  // this function monitors the connection between the ESP32 and wifi/bluetooth connection. If connection is lost the front red LED will light up. 

}


