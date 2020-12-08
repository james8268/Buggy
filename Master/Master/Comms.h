
//our communication header file. 

#ifndef Comms_h      
#define Comms_h

class Commsclass      //class name
{
public:
Commsclass();
    void SETUP();          //we have only two functions, the setup and one where it will read the message sent to the serial port from the bluetooth serial port 
    void read_message();



};

extern Commsclass Comms;

#endif
