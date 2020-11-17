
#include "arduino.h"
#include "Motor.h"
#include "Bluetooth.h"
#include "Ultra.h"
#include "operation.h"
#include "Servo.h"

Servo myservo;  //delares the servo movor as myservo. 

#define buzzer 30    // define the pins being used. 
#define tilt 23
#define espcom 2
#define esplost 35
#define espEN 34
#define LED 46
#define myserv 10

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
Serial.println("WARNING: BUGGY UNSTABLE");}  // a message is also sent the the user. 
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

void operationclass::noComs(){          // if the ESP32 loses connection to the wifi or bluetooth then the ESP32 sends a signal to the arduino mega to stop the buggy and wait 
  if (digitalRead(esplost)==HIGH){
    Motor.halt();
    digitalWrite(espEN,HIGH);     // a signal will be sent to the ESP32 to reset to regain connection to wifi or bluetooth 
    digitalWrite(LED,HIGH);  
    delay(2000);
    digitalWrite(LED,LOW);

    }
      digitalWrite(espEN, LOW);
      
  }


operationclass operation = operationclass();
