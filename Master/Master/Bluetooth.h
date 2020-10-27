
//our bluetooth header file. 

#ifndef Bluetooth_h      
#define Bluetooth_h

class Bluetoothclass      //class name
{
public:
Bluetoothclass();
    void SETUP();          //we have only two functions, the setup and one where it will read the message sent to the serial port from the bluetooth serial port 
    void read_message();
    


};

extern Bluetoothclass Bluetooth;

#endif
