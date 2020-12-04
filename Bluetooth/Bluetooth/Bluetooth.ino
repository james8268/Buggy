

#include "BluetoothSerial.h"
#include <Wire.h> 


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define lost 19

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
    Serial.println("Client Connected");
     digitalWrite(lost, LOW);
  }
 
  if(event == ESP_SPP_CLOSE_EVT ){
    Serial.println("Client disconnected");
      digitalWrite(lost, HIGH);
  }
  
}



void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name 
  pinMode(18,OUTPUT);
  pinMode(lost, OUTPUT);


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

    }
  
  SerialBT.register_callback(callback);



    
  }





  
