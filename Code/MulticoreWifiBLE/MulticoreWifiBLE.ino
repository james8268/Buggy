#include "BluetoothSerial.h"
#include <Wire.h> 


#define BLYNK_PRINT Serial    //defines the mobile deivce as a serial terminal

#include <WiFi.h>
#include <WiFiClient.h>         //include the needed header files, including the Blynk library.
#include <BlynkSimpleEsp32.h>



#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)         //enable Bluetooth.
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


String content = "";   
char character;

char auth[]= "jVAGDLSq2_VTo2K_l74wrM509taT5Bty";  // author token allows the Blynk app to to link with this project.

char ssid[]="VM9234142";    //internet SSID and password. 
char pass[]= "hgyb9tqPdhfw";

WidgetTerminal terminal(V1);   // declares the terminal is linked to the virtual pin 1.

BluetoothSerial SerialBT;

#define transmit 18   // pin 18 sends a signal to the Arduino when any transmition is occuring.
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
  //Bluetooth setup 
  Serial.begin(9600); 
  SerialBT.begin("ESP32test"); //Bluetooth device name 
  pinMode(transmit,OUTPUT);
  pinMode(lost, OUTPUT);

//WiFi setup
Blynk.begin(auth, ssid, pass);     // this is where the esp32 connects to the WiFi and Blynk servers. 
terminal.clear();                  // clear the mobile terminal
Blynk.virtualWrite(V1, "Welcome MR Ravenhill, I'm ready to recieve commands");     // welcome message printed in the mobile terminal.


  //core setup
xTaskCreatePinnedToCore(WiFiTask, "WiFi", 10000, NULL, 1, NULL,  1);   //create a task on one CPU that uses WiFi
  delay(500);  
xTaskCreatePinnedToCore(BluetoothTask, "Bluetooth", 10000, NULL, 1, NULL,  1);   //create another task on the remaining CPU to handle Bluetooth communication.
    delay(500); 
}


void WiFiTask( void * pvParameters ){      // This is the WiFi communication loop 
for(;;){

 Blynk.run();    //this runs all the Blynk functions 
SerialInput();

 if(WiFi.status() != WL_CONNECTED){digitalWrite(lost, HIGH);  //This monitors the WiFi connection. 
 setup();}
 else{digitalWrite(lost, LOW);}
    
  }
}

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){      //This callback is monitoring bluetooth connection.
  if(event == ESP_SPP_SRV_OPEN_EVT){
   
     digitalWrite(lost, LOW);
  }
 
  if(event == ESP_SPP_CLOSE_EVT ){
    
      digitalWrite(lost, HIGH);
  }
  
}

void BluetoothTask( void * pvParameters ){   //This loop is responsible for Bluetooth communication 
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

  SerialBT.register_callback(callback);   //This checks the Bluetooth connection using the callback function. 
  }
}


void loop() {
}
