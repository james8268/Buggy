// This is our main code.          // taken baud rates:9600(bluetooth), 4800 (Ultrasound)

#include "Arduino.h"
#include"Motor.h"
#include "Ultra.h"
#include "Bluetooth.h"
#include "Wire.h"


void setup() {

Motor.SETUP();
Ultra.SETUP();
Bluetooth.SETUP();


//pinMode(2,INPUT_PULLUP);

//attachInterrupt(digitalPinToInterrupt(2), Bluetooth_ISR, CHANGE);
}

void loop() {

//Motor.forwards1();
//delay(5000);
//Motor.forwards2();
//delay(5000);

//Motor.forwards3();



//Ultra.observe();
Ultra.dist();
Ultra.lcd_show(); //prints on the LCD and in the bluetooth terminal. 

Bluetooth.read_message();

}

//void Bluetooth_ISR(){
 // Motor.halt();
  //Bluetooth.read_message();
  
 // }

 // use an interrupt for overide control
