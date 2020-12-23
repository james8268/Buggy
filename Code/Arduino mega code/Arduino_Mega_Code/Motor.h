#ifndef Motor_h
#define Motor_h     //define our motor class.

class Motorclass
{
public:
Motorclass();
    void SETUP();       // multiple functions that speak for themselves, the set up sort the pinModes for the motors. 
    void forwards1();
    void forwards2();   // multiple forwards functions which correspond to the varying speeds of the motors.
    void forwards3();
    
    void backwards();  // functions to reverse, rotate left, rotate right and halt the buggy
    void left90();
    void right90();
    void halt();
 
  
    
};

extern Motorclass Motor;

#endif
