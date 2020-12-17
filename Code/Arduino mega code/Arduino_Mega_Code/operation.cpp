
#include "arduino.h"
#include "Motor.h"
#include "Ultra.h"          //most if not all the header files we have created will be used as this is the main operations source code file
#include "operation.h"
#include "Servo.h"
#include "IRremote.h"
#include "dht.h"
#include "LiquidCrystal_I2C.h" 


Servo myservo;  //delares the servo for the ultrasound sensor.   
Servo waterservo;  //declare the servo for the water sensor

#define buzzer 30    //buzzer pin for the tilt sensor 
#define tilt 23   // tilt sensor pin
#define espcom 2  //ESP32 communications pin
#define esplost 35    //ESP32 connection lost pin
#define LED 47    //Red LED pin
#define myserv 10   //ultrasound sensor servo motor pin
#define waterserv 26   //water sensor servo motor pin
int val=0; // this is the initial water value 
int pin= A8; // this is the signal pin from water sensor

#define recieverpin 46   //IR reciever pin
IRrecv irrecv(recieverpin);    //declare the IR reviever and the results it recieves.
decode_results results;


dht DHT;        //declare the temp/humidity sensor
#define DHT11_PIN 34  //temp/humidity sensor pin
LiquidCrystal_I2C screen(0x27,16,2);   //declare the I2C screen



operationclass::operationclass() {} // set up operation class

void(* resetFunc) (void) = 0; //declare reset function @ address 0


void operationclass::SETUP(){
  
screen.init();     //initalise the LCD 
screen.backlight();
  myservo.attach(myserv);
  waterservo.attach(waterserv);    //set up the pins, input or output
  pinMode(espcom,INPUT);
  pinMode(tilt, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(esplost, INPUT);
  pinMode(LED,OUTPUT);
  irrecv.enableIRIn();   //start the IR reader. 

  
  }


void operationclass::servl(){ //this makes the servo rotate so it is facing left 

    myservo.write(180);          // 180 degrees    
   
 }

void operationclass::servr(){  // this rotates the servo to face the right
 
    myservo.write(1);           // 1 degree, if 0 is used the servo gets stuck. 
   
  }
 
void operationclass::servc(){ //this rotates the servo the the centre (facing forwards)

    myservo.write(90);             // 90 degrees 

    }


void operationclass::h2o(){
                                //This function will take a watersensor reading. It will halt the buggy first so it doesnt break the sensor. 
Motor.halt();

waterservo.write(90);       //It makes sure the water sensor is up
delay(500);

waterservo.write(1);    //this moves the water sensor down so a reading can be taken.
screen.clear();
screen.setCursor(0,0); 
screen.print("Water level: ");
screen.setCursor(0,1);
delay(2000);

val=analogRead(pin);   //this pin reads the analogue inout front the water sensor. 

if(val<=300){screen.println("EMPTY           "); Serial.println("Water Level: EMPTY");}
else if (val>300 && val<=500){screen.println("LOW             "); Serial.println("Water Level: LOW");}
else if (val>500 && val<= 650){screen.println("MEDIUM          "); Serial.println("Water Level: MEDIUM");}
else if (val>650){screen.println("HIGH            "); Serial.println("Water Level: HIGH");}


delay(2000);

waterservo.write(90);
delay(500);
  
}

void operationclass::level(){    // This function monitors the tilt sensor. If the tilt sensor pin reads as low it will sound the buzzer and alert the user. 
if (digitalRead(tilt)==LOW){digitalWrite(buzzer, HIGH);
Motor.halt();
Serial.println("WARNING: BUGGY UNSTABLE");
delay(500);}  // a message is also sent the the user. 
else{digitalWrite(buzzer, LOW);    //this turns the buzzer off if the buggy is level. 
}

}


void operationclass::roam(){      // this is another important function. It allows the buggy to roam freely and observes its surroundings in order to avoid obstacles. 
for(;;){  
  
Ultra.observe(); 
Ultra.dist();
Ultra.lcd_show(); //prints on the LCD and in the bluetooth terminal.
if(digitalRead(espcom)==HIGH || digitalRead(tilt)==LOW || digitalRead(esplost)==HIGH){   // if communication via the mobile device happens or the tilt sensor is triggered or the esp has lost wifi or bluetooth connection 
                                                                                          // the buggy will stop and be reset to the main loop of the main code. 
  Serial.println("STOPPING, please wait ...... ");
  Motor.halt();
  delay(500);
  resetFunc();
  }  
}
}

void operationclass::measure(){
for(;;){  
  
Ultra.observe(); 
Ultra.dist();
if(Ultra.dist()<30){
h2o();
temp();}
Ultra.lcd_show(); //prints on the LCD and in the bluetooth terminal.
if(digitalRead(espcom)==HIGH || digitalRead(tilt)==LOW || digitalRead(esplost)==HIGH){   // if communication via the mobile device happens or the tilt sensor is triggered or the esp has lost wifi or bluetooth connection 
                                                                                          // the buggy will stop and be reset to the main loop of the main code. 
  Serial.println("STOPPING, please wait ...... ");
  Motor.halt();
  delay(500);
  resetFunc();
  }  
}

  
}

void operationclass::noINT(){          // if the ESP32 loses connection to the wifi or bluetooth then the ESP32 sends a signal to the arduino mega to stop the buggy and wait 
  if (digitalRead(esplost)==HIGH){
    Motor.halt();                     //when connection is lost the ESP32 send a signal to the arduino board. The buggy will halt and clear the LCD screen as a safety measure. 
    screen.clear();
    digitalWrite(LED,HIGH);         //The user will be notified by a Red LED light on the front of the buggy. 
    }
    else{digitalWrite(LED, LOW);}
   
}


void operationclass::translateIR(){      //Thsi function translates the hexadecimal IR input 
  
switch(results.value){

case 0xFFA25D:  Motor.forwards1(); break; //1
case 0xFF629D:  Motor.forwards2(); break; //2                      //Each button on the remote has a different Hex number 
case 0xFFE21D:  Motor.forwards3(); break; //3
case 0xFF22DD:  break; //4
case 0xFF02FD:  break; //5
case 0xFFC23D:  break; //6
case 0xFFE01F:  break; //7
case 0xFFA857:  break; //8
case 0xFF906F:  break; //9
case 0xFF9867:  break; //0
case 0xFF6897:  temp(); break; //*
case 0xFFB04F:  h2o(); break; //#
case 0xFF18E7:  Motor.forwards3(); break; //up
case 0xFF4AB5:  Motor.backwards(); break; //down
case 0xFF10EF:  Motor.left90(); break; //left
case 0xFF5AA5:  Motor.right90(); break; //right
case 0xFF38C7:  Motor.halt(); break; //ok
default: break;
}

}


void operationclass::IRread(){     //This function reads the incoming IR input from the remote. 
          
if (irrecv.decode(&results)){    //The Input is recieved from the IR remote 

//Serial.println(results.value, HEX);
translateIR();         //It is then translated from Hex to somethign with is useful
irrecv.resume();      // Then the input is cleared to carry on reading the input 

}}



void operationclass::temp(){         // This reads the temperature and humidity from the DHT11 sensor to the LCD screen and through the serial port. 
int chk = DHT.read11(DHT11_PIN);
screen.clear();
 screen.setCursor(0,0); 
  screen.print("Temp: ");
  Serial.print("TEMP: ");
  
  screen.print(DHT.temperature);
    Serial.print(DHT.temperature);

 screen.print((char)223);

  screen.print("C");
    Serial.println("C");

  screen.setCursor(0,1);
  screen.print("Humidity: ");
    Serial.print("Humidity: ");

  screen.print(DHT.humidity);
    Serial.print(DHT.humidity);

  screen.print("%");
    Serial.println("%");
  
}

  


operationclass operation = operationclass();
