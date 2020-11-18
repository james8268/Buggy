
#include "arduino.h"
#include "Motor.h"
#include "Bluetooth.h"
#include "Ultra.h"
#include "operation.h"
#include "Servo.h"
#include "IRremote.h"


Servo myservo;  //delares the servo movor as myservo. 

#define buzzer 30    // define the pins being used. 
#define tilt 23
#define espcom 2
#define esplost 35
#define espEN 34
#define LED 47
#define myserv 10


#define recieverpin 46
IRrecv irrecv(recieverpin);
decode_results results;


operationclass::operationclass() {} // set up operation class

void(* resetFunc) (void) = 0; //declare reset function @ address 0


void operationclass::SETUP(){
  myservo.attach(myserv);
  pinMode(espcom,INPUT);
  pinMode(tilt, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(esplost, INPUT);
  pinMode(espEN, OUTPUT);
  pinMode(LED,OUTPUT);
  irrecv.enableIRIn();
  }

void operationclass::servl(){ //this makes the servo rotate so it is facing left 

    myservo.write(180);          // 180 degrees    
   
 }

void operationclass::servr(){  // this rotates the servo to face the right
 
    myservo.write(1);           // 1 degree, if 0 is used the servo gets stuck. 
   
  }
 
void operationclass::servc(){ //this rotates the servo the the centre (facing forwards)

    myservo.write(90);             // 90 degrees 

    }

void operationclass::level(){    // This function monitors the tilt sensor. If the tilt sensor pin reads as low it will sound the buzzer and alert the user. 
if (digitalRead(tilt)==LOW){digitalWrite(buzzer, HIGH);
Motor.halt();
Serial.println("WARNING: BUGGY UNSTABLE");
delay(500);}  // a message is also sent the the user. 
else{digitalWrite(buzzer, LOW);    //this turns the buzzer off if the buggy is level. 
}

}


void operationclass::roam(){      // this is another important function. It allows the buggy to roam freely and observes its surroundings in order to avoid obstacles. 
for(;;){  

Ultra.observe(); 
Ultra.dist();
Ultra.lcd_show(); //prints on the LCD and in the bluetooth terminal.
if(digitalRead(espcom)==HIGH || digitalRead(tilt)==LOW || digitalRead(esplost)==HIGH){   // if communication via the mobile device happens or the tilt sensor is triggered or the esp has lost wifi or bluetooth connection 
                                                                                          // the buggy will stop and be reset to the main loop of the main code. 
  Serial.println("BREAKING");
  Motor.halt();
  delay(500);
  resetFunc();
  }  
}
}

void operationclass::noINT(){          // if the ESP32 loses connection to the wifi or bluetooth then the ESP32 sends a signal to the arduino mega to stop the buggy and wait 
  if (digitalRead(esplost)==HIGH){
    //digitalWrite(espEN,HIGH);
    Motor.halt();     // a signal will be sent to the ESP32 to reset to regain connection to wifi or bluetooth 
    digitalWrite(LED,HIGH);  
    delay(2000);
    digitalWrite(LED,LOW);
   //digitalWrite(espEN, LOW);
    }
   
}


void operationclass::translateIR(){
  
switch(results.value){

case 0xFFA25D: Motor.forwards1(); break; //1
case 0xFF629D: Motor.forwards2(); break; //2
case 0xFFE21D: Motor.forwards3(); break; //3
case 0xFF22DD: Serial.println("4"); break; //4
case 0xFF02FD: Serial.println("5"); break; //5
case 0xFFC23D: Serial.println("6"); break; //6
case 0xFFE01F: Serial.println("7"); break; //7
case 0xFFA857: Serial.println("8"); break; //8
case 0xFF906F: Serial.println("9"); break; //9
case 0xFF9867: Serial.println("0"); break; //0
//case 0xFF6897: Motor.halt(); delay(500); resetFunc(); break; //*
//case 0xFFB04F: roam(); break; //#
case 0xFF18E7: Motor.forwards3(); break; //up
case 0xFF4AB5: Motor.backwards(); break; //down
case 0xFF10EF: Motor.left90(); break; //left
case 0xFF5AA5: Motor.right90(); break; //right
case 0xFF38C7: Motor.halt(); break; //ok
default: break;
}
/*
0xFFA25D
 0xFF629D
 0xFFE21D
0xFF22DD
0xFF02FD
 0xFFC23D
 0xFFE01F
 0xFFA857
 0xFF906F
 0xFF9867
 0xFF6897
0xFF18E7
0xFF5AA5
 0xFF38C7
*/
}


void operationclass::IRread(){
//constrain(results.value, 0xFF02FD, 0xFFE21D);           add to roam if loop conditions 
if (irrecv.decode(&results)){

//Serial.println(results.value, HEX);
translateIR();
irrecv.resume();

}}

  


operationclass operation = operationclass();
