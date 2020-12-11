// This is the main code, It is uploaded to the Arduino Mega. It contains the setup functions for specific libraries. 

// taken baud rates:9600(bluetooth), 4800 (Ultrasound)

#include "Arduino.h"
#include"Motor.h"
#include "Ultra.h"
#include "Comms.h"   // Include all headers needed for the buggy's opertion
#include "Wire.h"
#include "operation.h"
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 5
bool correct=false;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup() {

Motor.SETUP();     
Ultra.SETUP();       // all the header files are setup. 
Comms.SETUP();
operation.SETUP();

SPI.begin();      // Initiate  SPI bus
mfrc522.PCD_Init();   // Initiate MFRC522
Serial.println("Approximate your card to the reader...");

}

void loop() {

RFID_CHALLENGE();

if(correct==true){ 
  Serial.println("Buggy ready for commands");
  for(;;){
    
if(Serial.available()){   //This allows the Buggy to be controlled via the serial monitor directly. ONLY UNCOMMENT IF STATEMENT WHEN USING. 
  Comms.read_message();
    }


operation.IRread(); //read the IR sensor if a order has been set from the controller
Comms.read_message();   // this reads messages sent over WiFi or Bluetooth to the esp32 and actions them. 


operation.level();  // this function will stop the buggy if the tilt sensor is triggered, a buzzer and warning message will alert the user. 
operation.noINT();  // this function monitors the connection between the ESP32 and wifi/bluetooth connection. If connection is lost the front red LED will light up. 
  }
}        

}



void RFID_CHALLENGE(){
  
  
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "04 5B 68 2B" || content.substring(1) == "77 A5 B1 7B" ) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    correct=true;
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
 
  
  }
