#include "encrypt.h"
#include "arduino.h"

int inByte=0;    //set the incoming data to and integer


encryptclass::encryptclass() {}

void encryptclass::SETUP(){   //this only sets up the serial port on a baud rate of 9600 

Serial.begin(9600);
  
}
                           //the encrypted data can be decrypted with the same function as its a rot 13 encryption. 
                           
void encryptclass::rot(int inByte){      //this is the function that will encrypt the incoming data
 
   if(Serial.available()> 0){    //when the serial port is availabe (i.e a message has been sent to the serial port) then start the encryption
     inByte = Serial.read();        //read the message in the serial port that has just been recieved.  

  if (inByte >= 'A' && inByte <= 'M'){     //any letters between A-M will be moved down the alphabet by 13 positions
     inByte += 13;
      } 
            
  else if (inByte >= 'N' && inByte <= 'Z'){  //any letters between N-Z will be moved up the alphabet but 13 positions
   inByte -= 13;}

      
  else if (inByte >= 'a' && inByte <= 'm'){
 inByte += 13;
  }                                                 // these are the same functions as above but for lower case letters.

  else if (inByte >= 'n' && inByte <= 'z'){
 inByte -= 13;

     } 
  Serial.write(inByte);    // write the encrypted message in the serial port. 

         } 

    }; 

encryptclass encrypt= encryptclass();
