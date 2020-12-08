#include "encrypt.h"
#include "arduino.h"

int inByte=0;


encryptclass::encryptclass() {}

void encryptclass::SETUP(){

Serial.begin(9600);
  
}


void encryptclass::rot(int inByte){
 
   if(Serial.available()> 0){
     inByte = Serial.read();        

  if (inByte >= 'A' && inByte <= 'M'){
     inByte += 13;
      } 
            
  else if (inByte >= 'N' && inByte <= 'Z'){
   inByte -= 13;}

      
  else if (inByte >= 'a' && inByte <= 'm'){
 inByte += 13;
  } 

  else if (inByte >= 'n' && inByte <= 'z'){
 inByte -= 13;

     } 
  Serial.write(inByte);  

         } 

    }; 

encryptclass encrypt= encryptclass();
