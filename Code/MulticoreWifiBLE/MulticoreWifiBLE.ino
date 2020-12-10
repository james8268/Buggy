#include "BluetoothSerial.h"
#include <Wire.h> 


#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>



#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


String content = "";
char character;

char auth[]= "jVAGDLSq2_VTo2K_l74wrM509taT5Bty";  // author token allows the Blynk app to to link with this project.

char ssid[]="VM9234142";    //internet SSID and passwork. 
char pass[]= "hgyb9tqPdhfw";

WidgetTerminal terminal(V1);   // declares the terminal is linked to the virtual pin 1.

BluetoothSerial SerialBT;

#define transmit 18   // pin 18 sends a signal to the Arduino 
#define lost 19       // pin 19 sends a signal to the arduino if the WiFi connection is lost, this allows the buggy to stop moving. 


BLYNK_WRITE(V1) {       // this function allows the terminal on the mobile device to communicate to the ESP32 Serial. 

  // Print all parameter values
  for (auto i = param.begin(); i < param.end(); ++i) { // this for loop sets the condtions needed to read the messages as a string from the terminal  
    Serial.println(i.asString());
   
  }
  digitalWrite(transmit, HIGH);   // when a string of communication recieved by the esp32 it will cause the transmit pin to output as high for half a second.
  delay(500);                    // This is then used by the arduino mega in the operation.roam() 
  digitalWrite(transmit, LOW);


}


void SerialInput() {
  if (Serial.available()) {  
    character = Serial.read();  // when a serial is available, read what has been printed
    content.concat(character); 
    if (character == '\n'){  
      Blynk.virtualWrite(V1, content);  // the characters have been gathered and are then sent to the mobile devices terminal 
      content = "";  // Clear the String to be able to reciver a new message without repeating what was said previously. 
    }
  }
}



void setup(){
  //Bluetooth setuo 
  Serial.begin(9600); 
  SerialBT.begin("ESP32test"); //Bluetooth device name 
  pinMode(transmit,OUTPUT);
  pinMode(lost, OUTPUT);

//WiFi setup
Blynk.begin(auth, ssid, pass);     // this is where the esp32 connects to the WiFi and Blynk Cloud. 
terminal.clear();                  // clear the mobile terminal
Blynk.virtualWrite(V1, "Welcome MR Ravenhill, I'm ready to recieve commands");     // welcome message printed in the mobile terminal.


  //core setup
xTaskCreatePinnedToCore(WiFiTask, "WiFi", 10000, NULL, 1, NULL,  1); 
  delay(500); 
xTaskCreatePinnedToCore(BluetoothTask, "Bluetooth", 10000, NULL, 1, NULL,  1); 
    delay(500); 
}


void WiFiTask( void * pvParameters ){
for(;;){
    // put your main code here, to run repeatedly:
 Blynk.run();    //this runs all the Blynk functions 
SerialInput();

if(Blynk.connected()==false){  // if connection is lost then this if loop is entered.  Blynk.connect() can be used to send a ping to the router. 
  digitalWrite(lost, HIGH);    // it communicates to the arduino mega through a digital pin 
 Serial.println("Connection lost");    // this is printed in the serial, if wifi connection is lost there will be no way to communicate to the mobile device so there is no need for this communication method. 
  delay(5000);
  digitalWrite(lost, LOW);}
    
  }
}


void BluetoothTask( void * pvParameters ){
  for(;;){
 if (SerialBT.available()){
      digitalWrite(transmit,HIGH);
      delay(200);
      Serial.write(SerialBT.read());
     }
 
 if (Serial.available()) {
    SerialBT.write(Serial.read());
  } 
  
  else{ 
    digitalWrite(transmit,LOW);

    }

if (SerialBT.connected()==false) {                              
    Serial.println("Disconnected!!");
 digitalWrite(lost, HIGH);    // it communicates to the arduino mega through a digital pin 
  delay(5000);
  digitalWrite(lost, LOW);}
  }
}


void loop() {
}
