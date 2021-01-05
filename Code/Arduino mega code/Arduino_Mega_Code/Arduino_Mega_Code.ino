// This is the main code, It is uploaded to the Arduino Mega. It contains the setup functions for specific libraries. 

// used baud rates: 9600(ESP32), 4800 (Ultrasound)

#include "Arduino.h"
#include "Motor.h"
#include "Ultra.h"
#include "Comms.h"   // Include all headers needed for the buggy's opertion
#include "Wire.h"
#include "operation.h"
#include "RFID.h"


void setup() {

Motor.SETUP();     
Ultra.SETUP();       // all the header files are setup. 
Comms.SETUP();
operation.SETUP();
RFID.RFIDsetup();
}

void loop() {



if(RFID.RFID_challenge()==true){    //Check if the RFID tag has been scanned, if so then it will be true and operation can commence
  Serial.println("Buggy ready for commands");
  for(;;){            
    
if(Serial.available()){   //This allows the Buggy to be controlled via the serial monitor when connected to a PC.  
 Comms.read_message();
  }

operation.IRread(); //read the IR sensor if a order has been sent from the controller
Comms.read_message();   // this reads recieved commands and performs the output function. 
operation.level();  // this function will stop the buggy if the tilt sensor is triggered, a buzzer and warning message will alert the user. 
operation.noINT();  // this function monitors the connection between the ESP32 and wifi/bluetooth connection. If connection is lost the front red LED will light up. 
  }
}        

}


  
