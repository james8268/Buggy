#include <WiFi.h>      //Include the needed header files
#include <WiFiClient.h>                                            

char ssid1[]="VM9234142";    // SSID and password. 
char pass[]= "hgyb9tqPdhfw";

#define lost 19     //pins that are used when communicationg to the Arduino mega and if network connection is lost. 
#define transmit 18    
 
WiFiServer server(80);   //Declare the port number. A socket will be needed to access communication on the mobile device.
 
void setup() {
 
 pinMode(lost, OUTPUT);          
 pinMode(transmit, OUTPUT);
  Serial.begin(9600);
  Serial.println();       
  WiFi.begin(ssid1, pass);     //Initiate WiFi with SSID and Password
 
  server.begin();    //initiate the server
 
  Serial.println("Server started");
     
    while (WiFi.status() != WL_CONNECTED) {    //If the WiFi status is not connected then display a waiting/loading message
      
        delay(500);
        Serial.print(".");
    }

    Serial.println("");                //When then ESP32 is connected to WiFi display the connected message and IP address.  
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

      while(client.connected()){       //If the mobile device send a command then is will be recieved by the ESP32 and sent to the Arduino mega.
        if(client.available()){
          char c=client.read();
          Serial.println(c);
          digitalWrite(transmit,HIGH);
          delay(500);
          digitalWrite(transmit, LOW);
          }

           if(Serial.available()){          //This will print any messages sent from the Arduino mega and will display them on the mobile device.
             client.write(Serial.read());
             
           }
        
        
      }
      }
String line="";

}
