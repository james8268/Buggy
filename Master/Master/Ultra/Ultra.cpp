#include "arduino.h"
#include "Ultra.h"

const uint8_t trigpin = 40;
const uint8_t echopin = 41;

const long dur;
const int dist;


Ultraclass::Ultraclass() {} // setup motor class

void Motorclass::SETUP() { //setup function

    pinMode(trigpin, OUTPUT);
    pinMode(echopin, INPUT);


}

void Ultraclass::dist() {  //function to find distance from ultrasonic sensor 

    digitalWrite(trigpin, LOW); // Clears the trigpin
    delayMicroseconds(2);

    digitalWrite(trigpin, HIGH); // Sets the trigpin on HIGH state for 10 micro seconds
    delay(10);
    digitalWrite(trigpin, LOW);


    dur = pulseIn(echopin, HIGH); // Reads the echopin, returns the sound wave travel time in microseconds

    dist = dur * 0.034 / 2; // Calculating the distance


};


Ultraclass Ultra = Ultraclass();