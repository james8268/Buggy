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
              // sensor to detect obstruction/obstackles, it will halt the buggy and rotate the servo left and right finding the greatest clearance. 
if (distance <= 30 ){  //if there is a distance reading under 30cm, There is an obstackle in front of the buggy

  Motor.halt();
operation.servc();   //this function moves rotates the Ultrasound sensor to face the front (it should already be ther but this double checks).
int cdist=dist();          // create an integer of the distance to the front and measure this distance
Serial.print("C dist: ");
Serial.println(cdist);
delay(1000);       
operation.servl();    //rotate the servo so the ultrasound senspr faces the left.
delay(1000);
int ldist=dist();     // again we create and integer for the distance to the left and measure this distance 
Serial.print("L dist: ");
Serial.println(ldist);
delay(1000);

operation.servc();    //rotate the servo so the ultrasound sensor is back at the sensor.

delay(1000);       

operation.servr(); //rotate the servo to move the ultrasound to the right 
delay(1000);
int rdist=dist();   //take a reading of the measurement to the right and call it an integer
Serial.print("R dist: ");
Serial.println(rdist);
delay(1000);
operation.servc();

if (ldist>rdist && ldist>=cdist){Serial.println("ROAM: Left turn"); Motor.left90();}    // these if and else if statements makes the decision to turn left, 
                                                                                          // right or forwards.  
else if(cdist>ldist && cdist>=rdist){Serial.println("ROAM: Forwards"); Motor.forwards3();}
else if(rdist>ldist && rdist>=cdist){Serial.println("ROAM: Right turn"); Motor.right90();}
else{Serial.println("ROAM:U-turn"); Motor.right90(); Motor.right90();}

}

if (distance > 30){      //if there is no obstruction within 30cm the buggy will move forwards at full speed 
Motor.forwards3();}

  
};


Ultraclass Ultra = Ultraclass();
