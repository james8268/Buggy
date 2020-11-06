
#include "arduino.h"
#include "Motor.h"
#include "Bluetooth.h"
#include "Ultra.h"
#include "operation.h"


operationclass::operationclass() {} // set up operation class

void operationclass::roam(){
while(1){
Ultra.observe(); //could also be an interrupt function as is not always needed. 
Ultra.dist();
Ultra.lcd_show(); //prints on the LCD and in the bluetooth terminal. 
if (digitalRead(2)==HIGH){break;}  
}
};



operationclass operation = operationclass();
