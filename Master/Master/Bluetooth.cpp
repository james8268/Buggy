
#include "arduino.h"
#include "Motor.h"
#include "Bluetooth.h"
#include "Ultra.h"
#include "operation.h"

char incomingChar;   // set the incoming serial as characters. 


Bluetoothclass::Bluetoothclass() {} // setup Bluetooth class  

void Bluetoothclass::SETUP() { //setup function
  Serial.begin(9600);        // serial port baud rate 9600
  /*
  Serial.println("||   / |  / /                                                        /|    //| |             ");
Serial.println("||  /  | / /  ___     //  ___      ___      _   __      ___         //|   // | |     __     ");
Serial.println("|| / /||/ / //___) ) // //   ) ) //   ) ) // ) )  ) ) //___) )     // |  //  | |   //  ) )  ");
Serial.println("||/ / |  / //       // //       //   / / // / /  / / //           //  | //   | |  //        ");
Serial.println("|  /  | / ((____   // ((____   ((___/ / // / /  / / ((____       //   |//    | | //         ");
Serial.println("");
Serial.println("");
Serial.println("    //   ) )                                                         ");
Serial.println("   //___/ /   ___              ___       __     / __     ( ) // //   ");
Serial.println("  / ___ (   //   ) ) ||  / / //___) ) //   ) ) //   ) ) / / // //    ");
Serial.println(" //   | |  //   / /  || / / //       //   / / //   / / / / // //     ");
Serial.println("//    | | ((___( (   ||/ / ((____   //   / / //   / / / / // //      ");
*/
Serial.println("Buggy Ready");

}

void Bluetoothclass::read_message() { //read the serial function

if (Serial.available()){      // if there is a serial avalible then read it and call them the incomingchar
   char incomingChar = Serial.read();

   

switch(incomingChar){     // switch function acts as a simplified if fucntion, it will output the functions from our motor class depending on the character given
  
  case '1':
  Serial.println("REMOTE: forwards1");
  Motor.forwards1();     // "1" read from the serial port will move the buggy forward at speed 1 (Lowest speed)
  break;
  case '2':
  Serial.println("REMOTE: forwards2");
  Motor.forwards2();    // "2" read from the serial port will move the buggy forward at speed 2 (middle speed) 
  break;
  case '3':
  Serial.println("REMOTE: forwards3");
  Motor.forwards3();     // "3" read from the serial port will move the buggy forward at speed 3 (fastest speed)
  break;
  case 'b':
  Serial.println("REMOTE: reversing");
  Motor.backwards();     //"b" read from the serial port will move the buggy backwards
  break;
  case 'l':
  Serial.println("REMOTE: left turn");
  Motor.left90();       //"l" read from the serial port will rotate the buggy left approx 90 degrees dependant on environment
  break;
  case 'h':
  Serial.println("REMOTE: stopped");          
  Motor.halt();       //"h" read from the serial port will halt the buggy until told what to do otherwise.
  break;
  case 'r':
  Serial.println("REMOTE: right turn");
  Motor.right90();    // "r" read from the serial port will rotate the buggy right by approx 90 degrees dependant on environment
  break;
  case 'E':
  Serial.println("ROAMING");  // "E" will be read from the serial port and will allow the buggy to roam freely.
  operation.roam();
  break;
case 'T':
operation.temp();
break;
case 'W':
operation.h2o();
break;
case 'M':
Serial.println("Measuring Temp and H2O level at perimeter.");
operation.measure();
break; 




}

incomingChar="";    // set the incomingchar to a null value, this will allow the next command to be read from the serial port.
}


};



Bluetoothclass Bluetooth = Bluetoothclass();
