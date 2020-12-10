#ifndef Ultra_h
#define Ultra_h  //create our header file



class Ultraclass   //setup our ultrasound class
{

public:
    Ultraclass();
    void SETUP();    // our functions listed below will set up our ultrasound sensor aswell 
                    //as other usefull functions to find the distance using the ultrasound sensor and the observe function. 
    int dist();
    void lcd_show();
    long duration;
    int distance;
    void observe();


};

extern Ultraclass Ultra;

#endif
