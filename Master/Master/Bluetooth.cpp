
#include "arduino.h"
#include "Motor.h"
#include "Bluetooth.h"

String message = "";  // set our message as an empty string
char incomingChar;   // set the incoming serial as characters. 



Bluetoothclass::Bluetoothclass() {} // setup Bluetooth class  

void Bluetoothclass::SETUP() { //setup function
  Serial.begin(9600);        // serial port baud rate 9600

}

void Bluetoothclass::read_message() { //read the serial function

if (Serial.available()){                    // if there is a serial avalible then read it and call them the incomingchar
   char incomingChar = Serial.read();
  // if (incomingChar != '\n'){
    //  message += incomingChar;}

switch(incomingChar){     // switch function acts as a simplified if fucntion, it will output the functions from our motor class depending on the character given
  
  case '1':
  Motor.forwards1();     // "1" read from the serial port will move the buggy forward at speed 1 (Lowest speed)
  break;
  case '2':
  Motor.forwards2();    // "2" read from the serial port will move the buggy forward at speed 2 (middle speed) 
  break;
  case '3':
  Motor.forwards3();     // "3" read from the serial port will move the buggy forward at speed 3 (fastest speed)
  break;
  case 'b':
  Motor.backwards();     //"b" read from the serial port will move the buggy backwards
  break;
  case 'l':
  Motor.left90();       //"l" read from the serial port will rotate the buggy left approx 90 degrees dependant on environment
  break;
  case 'h':          
  Motor.halt();       //"h" read from the serial port will halt the buggy until told what to do otherwise.
  break;
  case 'r':
  Motor.right90();    // "r" read from the serial port will rotate the buggy right by approx 90 degrees dependant on environment
  break;
   
  
  }
  incomingChar="";    // set the incomingchar to a null value, this will allow the next command to be read from the serial port.
}

     

};



Bluetoothclass Bluetooth = Bluetoothclass();
