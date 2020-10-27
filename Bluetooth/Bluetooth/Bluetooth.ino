
#include "BluetoothSerial.h"
#include <Wire.h> 

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

String message = "";
char incomingChar;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name 
pinMode(18,OUTPUT);

}

void loop() {  
  
  if (SerialBT.available()){
Serial.write(SerialBT.read());
digitalWrite(18,HIGH);
    /*
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
      */  
  }
    else{message = "";
    digitalWrite(18,LOW);
    }}
    


  
