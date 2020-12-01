#include <WiFi.h>
#include <WiFiClient.h>                                            
#include <WiFiAP.h>



const char *ssid = "yourAP";
const char *password = "RavenMan98";

char ssid1[]="VM9234142";    // SSID and passwork. 
char pass[]= "hgyb9tqPdhfw";
 
WiFiServer server(80);

unsigned long prevMillis;
 unsigned long curMillis;
 
void setup() {
 
 
  Serial.begin(9600);
  Serial.println();
 // Serial.println("Configuring access point...");
  WiFi.begin(ssid1, pass);
 
  // You can remove the password parameter if you want the AP to be open.
//  WiFi.softAP(ssid, password);
 // IPAddress myIP = WiFi.softAPIP();
 // Serial.print("AP IP address: ");
 // Serial.println(myIP);
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
    prevMillis=millis();
}

void loop() {
  // put your main code here, to run repeatedly:
 
 curMillis=millis();
  if(curMillis-prevMillis >= 100){
printWifiStatus();}


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
prevMillis=curMillis;
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  
}
