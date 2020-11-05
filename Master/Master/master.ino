// This is the main code.          // taken baud rates:9600(bluetooth), 4800 (Ultrasound)

#include "Arduino.h"
#include"Motor.h"
#include "Ultra.h"
#include "Bluetooth.h"
#include "Wire.h"
#include "operation.h"

volatile bool roam = false; 

void setup() {

Motor.SETUP();
Ultra.SETUP();
Bluetooth.SETUP();


pinMode(2,INPUT);
attachInterrupt(digitalPinToInterrupt(2), Bluetooth_ISR, RISING);
}

void loop() {


Serial.println("ROAMING");
//Ultra.observe(); //could also be an interrupt function as is not always needed. 
//Ultra.dist();
//Ultra.lcd_show(); //prints on the LCD and in the bluetooth terminal. 
//Bluetooth.read_message(); 


if (roam=false){
Serial.println("Remote mode entered");
Bluetooth.read_message();  
}

}

void Bluetooth_ISR(){
  roam=false;}

 // use an interrupt for overide control
