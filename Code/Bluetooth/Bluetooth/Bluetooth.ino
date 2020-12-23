

#include "BluetoothSerial.h"
#include <Wire.h>            //Include the header files that will be needed. 
#include "encrypt.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)            //Enable Bluetooth connection for the ESP32 
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;   //setup up the Bluetooth serial which will be present on the mobile device. 

#define lost 19      //define the transmit pin which is used to signal to the Arduino mega that communication is happening. Lost pin will be triggered if Bluetooth connection is lost.
#define transmit 18

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){     //Callback function that monitors the Bluetooth connection. 
  if(event == ESP_SPP_SRV_OPEN_EVT){
   
     digitalWrite(lost, LOW);
  }
 
  if(event == ESP_SPP_CLOSE_EVT ){
    
      digitalWrite(lost, HIGH);
  }
  
}



void setup() {  //Setup function will setup input/output of pins and begine the serials that are needed. 
  Serial.begin(9600);      
  SerialBT.begin("ESP32test"); //Bluetooth device name 
  pinMode(transmit,OUTPUT);
  pinMode(lost, OUTPUT);


}

void loop() {  

  if (SerialBT.available()){     //If the mobile device sends a command to the ESP32 then this will read the commands and then send them to the Arduino Mega
      digitalWrite(transmit,HIGH);
      delay(200);
      Serial.write(SerialBT.read());
     } 
 if (Serial.available()) {         //If any messages are sent from the Arduino mega they are then relayed to the mobile device. 
    SerialBT.write(Serial.read());
  } 
  else{ 
    digitalWrite(transmit,LOW);

    }
  
  SerialBT.register_callback(callback);   //This is the callback function that monitors the Bluetooth connection to/from the EPS32 and the mobile device. 

    
  }





  
