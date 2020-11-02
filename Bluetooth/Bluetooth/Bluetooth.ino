
#include "BluetoothSerial.h"
#include <Wire.h> 

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name 
pinMode(18,OUTPUT);

}

void loop() {  
   
  if (SerialBT.available()){
      digitalWrite(18,HIGH);
      delay(200);
      Serial.write(SerialBT.read());
 }

   if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  
    else{
    digitalWrite(18,LOW);
    }}
    


  
