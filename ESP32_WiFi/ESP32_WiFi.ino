#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

String content = "";
char character;

char auth[]= "jVAGDLSq2_VTo2K_l74wrM509taT5Bty";

char ssid[]="VM9234142";

char pass[]= "hgyb9tqPdhfw";

WidgetTerminal terminal(V1);

  

BLYNK_WRITE(V1) {  

  // Print all parameter values
  for (auto i = param.begin(); i < param.end(); ++i) {
    Serial.println(i.asString());
   
  }
   digitalWrite(2, HIGH);
      digitalWrite(18, HIGH);

   delay(500);
  digitalWrite(2, LOW);
  digitalWrite(18, LOW);

}


void SerialInput() {
  if (Serial.available()) {  // Watch for Serial data
    character = Serial.read();  // Read Serial character
    content.concat(character);  // Add character to holding String
    if (character == '\n'){  // If last character is new line...
      Blynk.virtualWrite(V1, content);  // ...send string to terminal
      content = "";  // Clear holding String
    }
  }
}

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

Blynk.begin(auth, ssid, pass);
terminal.clear();
Blynk.virtualWrite(V1, "Welcome MR Ravenhill, I'm ready to recieve commands");
pinMode(2,OUTPUT);
pinMode(18,OUTPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
 Blynk.run();
SerialInput();

}
