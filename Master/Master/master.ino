// This is our main code.          // taken baud rates:9600(bluetooth), 4800 (Ultrasound)

#include "Arduino.h"
#include"Motor.h"
#include "Ultra.h"
#include "Bluetooth.h"
#include "Wire.h"

volatile bool Move=false;

void setup() {

Motor.SETUP();
Ultra.SETUP();
Bluetooth.SETUP();


pinMode(2,INPUT);
attachInterrupt(digitalPinToInterrupt(2), Bluetooth_ISR, RISING);
}

void loop() {
  
//Motor.forwards3();
Ultra.observe(); //could also be an interrupt function as is not always needed. 
Ultra.dist();
Ultra.lcd_show(); //prints on the LCD and in the bluetooth terminal. 

if (Move=true){
Move= false; 
Bluetooth.read_message();
}

}

void Bluetooth_ISR(){
Move=true; 
 }

 // use an interrupt for overide control
