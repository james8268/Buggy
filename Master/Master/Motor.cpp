#include "arduino.h"
#include "Motor.h"          //include our header file

const uint8_t dirA = 12;    //set up the pins which correspond to direction, break and PWM of our two DC motors.
const uint8_t dirB = 13;
const uint8_t brA = 9;
const uint8_t brB = 8;
const uint8_t pwmA = 3;
const uint8_t pwmB = 11;


Motorclass::Motorclass() {} // setup motor class

void Motorclass::SETUP() { //setup function

    pinMode(dirA, OUTPUT);  //all direction and break pins are set to OUTPUT. 
    pinMode(dirB, OUTPUT);
    pinMode(brA, OUTPUT);
    pinMode(brB, OUTPUT);

}

void Motorclass::forwards1() {  //function to move buggy forward 

    digitalWrite(dirA, HIGH);
    analogWrite(pwmA, 100);         //both motors will move in the same direction, due to them being in a opposing setup on will be set to HIGH and the other LOW
                                    // this will move both motors in a forwards direction in our global coordinates 
    digitalWrite(brA, LOW);

    digitalWrite(dirB, LOW);
    analogWrite(pwmB, 100);        //the power output sits at 100/255.
    digitalWrite(brB, LOW);
}


void Motorclass::forwards2() {  //function to move buggy forward 


     digitalWrite(dirA, HIGH);
    analogWrite(pwmA, 175);
    digitalWrite(brA, LOW);

    digitalWrite(dirB, LOW);
    analogWrite(pwmB, 175);        //the power output sits at 175/255
    digitalWrite(brB, LOW);
}

void Motorclass::forwards3() {  //function to move buggy forward 

     digitalWrite(dirA, HIGH);
    analogWrite(pwmA, 255);
    digitalWrite(brA, LOW);

    digitalWrite(dirB, LOW);
    analogWrite(pwmB, 255);    //the power sits at its maximum PWM 255/255.
    digitalWrite(brB, LOW);  
      
}
 



void Motorclass::backwards() {  // function to move buggy backwards at PWM 200/255

    digitalWrite(dirA, LOW);
    digitalWrite(brA, LOW);     
    analogWrite(pwmA, 200);

    digitalWrite(dirB, HIGH);
    digitalWrite(brB, LOW);
    analogWrite(pwmB, 200);
    delay(1000);
}

void Motorclass::halt() {  // function to stop buggy from moving by applying both breaks
    digitalWrite(brA, HIGH);

    digitalWrite(brB, HIGH);
    delay(500);

}

void Motorclass::left90() {  // function to rotate buggy to left by setting both motors clockwise at PWM 200/255

    digitalWrite(dirA, LOW); 
    analogWrite(pwmA, 200);
    digitalWrite(brA, LOW);
   

    digitalWrite(dirB, LOW);
    digitalWrite(brB, LOW);
    analogWrite(pwmB, 200);

    delay(500);

    halt();
}


void Motorclass::right90() {  //function to rotate buggy to the right by setting both motors anticlockwise at PWM 200/255

    digitalWrite(dirA, HIGH);
     analogWrite(pwmA, 200);
    digitalWrite(brA, LOW);
    

    digitalWrite(dirB, HIGH);
    digitalWrite(brB, LOW);
    analogWrite(pwmB, 200);

    delay(500);

    halt();

};


Motorclass Motor = Motorclass();
