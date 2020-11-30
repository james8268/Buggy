#include <WiFi.h>
#include <WiFiClient.h>                                            ///////////////////////This works ok but AP cant connect to internet. 
#include <WiFiAP.h>
 

// Set these to your desired credentials.
const char *ssid = "yourAP";
const char *password = "RavenMan98";

char ssid1[]="VM9234142";    //internet SSID and passwork. 
char pass[]= "hgyb9tqPdhfw";
 
WiFiServer server(80);
 
 
void setup() {
 
 
  Serial.begin(9600);
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.begin(ssid1, pass);
 
  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
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
  
  WiFiClient client = server.available();   // listen for incoming clients
 
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
 
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
           client.println("Content-type:text/html");
            client.println();
 
            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/h\">here</a> to Halt the buggy.<br>");
            client.print("Click <a href=\"/l\">here</a> to turn the buggy LEFT.<br>");
             client.print("Click <a href=\"/r\">here</a> to turn the buggy RIGHT.<br>");
              client.print("Click <a href=\"/1\">here</a> to move forwards SLOWLY.<br>");
               client.print("Click <a href=\"/2\">here</a> to move forwards.<br>");
                client.print("Click <a href=\"/3\">here</a> to move forwards FAST.<br>");
                 client.print("Click <a href=\"/E\">here</a> to turn ROAM.<br>");
                  client.print("Click <a href=\"/b\">here</a> to reverse the buggy.<br>");
                 
 
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
 

        if (currentLine.endsWith("GET /h")) {
         
          server.println("h");
        }
        if (currentLine.endsWith("GET /l")) {
         
           server.println("l");              
        }
        if (currentLine.endsWith("GET /r")) {
          
           server.println("r");              
        }
        if (currentLine.endsWith("GET /1")) {
          
          server.println("1");               
        }
        if (currentLine.endsWith("GET /2")) {
         
          server.println("2");             
        }
        if (currentLine.endsWith("GET /3")) {
        
         server.println("3");               
        }
        if (currentLine.endsWith("GET /E")) {
          
         server.println("E");             
        }
       if (currentLine.endsWith("GET /b")) {
      
          server.println("b");               
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  
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

 
