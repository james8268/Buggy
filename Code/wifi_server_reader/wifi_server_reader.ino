#include <WiFi.h>
#include <WiFiClient.h>                                            





char ssid1[]="VM9234142";    // SSID and passwork. 
char pass[]= "hgyb9tqPdhfw";

#define lost 19  
 
WiFiServer server(80);
 
void setup() {
 
 
  Serial.begin(9600);
  Serial.println();
  WiFi.begin(ssid1, pass);
 
  server.begin();
 
  Serial.println("Server started");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  
}

void loop() {

 if(WiFi.status() != WL_CONNECTED){digitalWrite(lost, HIGH);  //This monitors the WiFi connection. 
 setup();}
 else{digitalWrite(lost, LOW);}
  
    WiFiClient client = server.available();   // listen for incoming clients

    if (client){
      String line=""; 

      while(client.connected()){
        if(client.available()){
          char c=client.read();
          Serial.println(c);

           if(Serial.available()){
            client.flush();
            client.println(Serial.read());
             
           }
        }
        
      }
      }
String line="";

}
