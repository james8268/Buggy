#include <SPI.h>
#include <MFRC522.h>
#include "RFID.h"
#include "LiquidCrystal_I2C.h"

#define SS_PIN 53  //RFID SS and RST pins 
#define RST_PIN 5
bool correct=false;


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

LiquidCrystal_I2C disp(0x27,16,2);   //declare the I2C screen


RFIDclass::RFIDclass() {}

void RFIDclass::RFIDsetup(){
  Serial.begin(9600);
disp.init();
disp.backlight();
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Present your card to the reader...");
  disp.clear();
  disp.print("Present RFID Tag/Card...");
  
}

bool RFIDclass::RFID_challenge(){

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
    disp.clear();
    disp.print("Access Granted");
    correct=true;
    delay(3000);
    disp.clear();
  }
 
 else   {
    Serial.println("Access denied, try again...");
    disp.clear();
    disp.print("Access Denied");
    disp.setCursor(0,1);
    disp.print("try again...");
    delay(3000);
    disp.clear();
  }
 
  return correct;
  
  };

RFIDclass RFID = RFIDclass();
