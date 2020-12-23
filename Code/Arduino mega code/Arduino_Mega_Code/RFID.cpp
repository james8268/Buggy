#include <SPI.h>
#include <MFRC522.h>     //Include to needed header files
#include "RFID.h"
#include "LiquidCrystal_I2C.h"

#define SS_PIN 53  //RFID SS and RST pins 
#define RST_PIN 5
bool correct=false;   //initially set the RFID correct to false. 


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

LiquidCrystal_I2C disp(0x27,16,2);   //declare the I2C screen


RFIDclass::RFIDclass() {}

void RFIDclass::RFIDsetup(){   //RFID setup functon
  Serial.begin(9600);
disp.init();           //display settings 
disp.backlight();
  SPI.begin();      // Initiate SPI bus  
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Present your card to the reader...");    //ask to present the RFID tag to the reader. 
  disp.clear();
  disp.print("Present RFID Tag/Card...");
  
}

bool RFIDclass::RFID_challenge(){     //this is the challenge function which will accept or deny access to the buggy. 

      if ( ! mfrc522.PICC_IsNewCardPresent())    //this monitors if a card is not presented to the reader and will return nothing. 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())     //similar here where the reader reads a card. 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");        // If a new card is presented and is read then it will enter this part. Here the data on the card is read and stored. 
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
  if (content.substring(1) == "04 5B 68 2B" || content.substring(1) == "77 A5 B1 7B" ) //If the data read off the RFID card/tag mathes any of these strings then allow access to the buggy.
  {
    Serial.println("Authorized access");
    disp.clear();
    disp.print("Access Granted");
    correct=true;      //because we now have the correct access card/tag we say correct=true and this will allow access to the main code. 
    delay(3000);
    disp.clear();
  }
 
 else   {
    Serial.println("Access denied, try again...");    //If it does not match then acces is denied and a re-attempt is allowed. 
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
