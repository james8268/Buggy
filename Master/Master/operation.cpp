
#include "arduino.h"
#include "Motor.h"
#include "Bluetooth.h"
#include "Ultra.h"
#include "operation.h"

char message;

operationclass::operationclass() {} // set up operation class

void operationclass::roam(){

Ultra.observe(); //could also be an interrupt function as is not always needed. 
Ultra.dist();
Ultra.lcd_show(); //prints on the LCD and in the bluetooth terminal. 

}

void operationclass::remote(){
  Serial.begin(9600);
  if (Serial.available()){                    // if there is a serial avalible then read it and call them the incomingchar
   char message = Serial.read();}
  
  switch(message){

case'E':

Serial.println("Remote mode entered");
Bluetooth.read_message();  
break;
 
   case 'X':
   Serial.println("ROAMING");
   roam();
   break;
   
   }
  
message="";
  };

operationclass operation = operationclass();
