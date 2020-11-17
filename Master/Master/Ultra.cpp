#include "arduino.h"
#include "Ultra.h"
#include "LiquidCrystal_I2C.h"    //aswell as our header file we have included a few other libraries which will be used.
#include "Motor.h"
#include "operation.h"

LiquidCrystal_I2C lcd(0x27,16,2);  //sets up and calls on our I2C LCD 


const uint8_t trigpin = 40;   // our trig and echo pin numbers
const uint8_t echopin = 41;


Ultraclass::Ultraclass() {} // setup ultra class

void Ultraclass::SETUP() { //setup function

    pinMode(trigpin, OUTPUT);   // creates our pin modes aswell as initializing out I2C LCD below.  
    pinMode(echopin, INPUT);
    lcd.init();
lcd.backlight();

}

int Ultraclass::dist() {  //function to find distance from ultrasound sensor to an obstacle 

    digitalWrite(trigpin, LOW); // Clears the trigpin
    delayMicroseconds(2);

    digitalWrite(trigpin, HIGH); // Sets the trigpin on HIGH state for 10 micro seconds and then low again
    delay(10);
    digitalWrite(trigpin, LOW);

duration = pulseIn(echopin, HIGH); // Reads the echopin, returns the sound wave travel time in microseconds
distance = (duration*0.034)/2 ; // Calculating the distance

return distance;

}

void Ultraclass::lcd_show(){  //this print the distance in our I2C LCD. 
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Distance: ");
lcd.print(distance);
lcd.print("CM");
delay(200);
Serial.begin(9600);
if (Serial.available()){                    // if there is a serial avalible then print the distance to it
   Serial.print("Distance: ");
   Serial.print(distance);
   Serial.println("CM");}
}

void Ultraclass::observe(){   //this is a crucial function if the buggy is being left to move freely without human interaction. it uses the ultarsound
                              // sensor to detect obstruction, it will halt the buggy and rotate left the servo left and right finding the greatest clearance. 
if (distance <= 30 ){

  Motor.halt();
operation.servc();

operation.servl();
delay(1000);
int ldist=dist();
delay(1000);

operation.servc();

delay(1000);

operation.servr();
delay(1000);
int rdist=dist();
delay(1000);
operation.servc();

if (ldist>rdist){Motor.left90();}    // this if loop makes the decision to turn left or right. 
else {Motor.right90();}

}

if (distance > 30){      //if ther is no obstruction within 30cm the buggy will move forwards at full speed 
Motor.forwards3();}

  
};


Ultraclass Ultra = Ultraclass();
