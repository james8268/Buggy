// This sketch is to be uploaded to the ESP32 when a WiFi connection is wanted rather than a Bluetooth connection. 


#define BLYNK_PRINT Serial    

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


#define transmit 18   // pin 18 sends a signal to the Arduino 
#define lost 19       // pin 19 sends a signal to the arduino if the WiFi connection is lost, this allows the buggy to stop moving. 

String content = "";
char character;

char auth[]= "jVAGDLSq2_VTo2K_l74wrM509taT5Bty";  // author token allows the Blynk app to to link with this project.

char ssid[]="VM9234142";    //internet SSID and passwork. 
char pass[]= "hgyb9tqPdhfw";


WidgetTerminal terminal(V1);   // declares the terminal is linked to the virtual pin 1.

  

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

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);     // this is where the esp32 connects to the WiFi and Blynk Cloud. 
terminal.clear();                  // clear the mobile terminal
Blynk.virtualWrite(V1, "Welcome MR Ravenhill, I'm ready to recieve commands");     // welcome message printed in the mobile terminal.
pinMode(transmit,OUTPUT);   //pin set ups for the transmit and lost pin. 
pinMode(lost, OUTPUT);

}



void loop() {
  // put your main code here, to run repeatedly:
 
 Blynk.run();    //this runs all the Blynk functions 
SerialInput();

 if(WiFi.status() != WL_CONNECTED){digitalWrite(lost, HIGH);  //This monitors the WiFi connection. 
 setup();}
 else{digitalWrite(lost, LOW);}

}
