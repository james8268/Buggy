
#include "arduino.h"
#include "Motor.h"
#include "Bluetooth.h"
#include "Ultra.h"
#include "operation.h"

#include "Servo.h"

Servo myservo;

#define buzzer 30
#define tilt 31


operationclass::operationclass() {} // set up operation class

void(* resetFunc) (void) = 0; //declare reset function @ address 0


void operationclass::SETUP(){
  myservo.attach(10);
  pinMode(2,INPUT);
  pinMode(tilt, INPUT);
  pinMode(buzzer, OUTPUT);
  }

void operationclass::servl(){

    myservo.write(180);              
   
 }

void operationclass::servr(){
 
    myservo.write(1);           
   
  }
 
void operationclass::servc(){

    myservo.write(90);             

    }

void operationclass::level(){
if (digitalRead(tilt)==HIGH){digitalWrite(buzzer, LOW);}
else{digitalWrite(buzzer, HIGH);
Motor.halt();
Serial.println("WARNING: BUGGY UNSTABLE");}

}


void operationclass::roam(){
for(;;){  

Ultra.observe(); //could also be an interrupt function as is not always needed. 
Ultra.dist();
Ultra.lcd_show(); //prints on the LCD and in the bluetooth terminal.
level();
if(digitalRead(2)==HIGH){
  Serial.println("BREAKING");
  Motor.halt();
  resetFunc();
  }  
}
}


operationclass operation = operationclass();
