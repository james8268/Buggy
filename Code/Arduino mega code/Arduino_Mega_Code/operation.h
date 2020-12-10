#ifndef operation_h
#define operation_h  //create our header file



class operationclass   //setup the operation class
{

public:
    operationclass();

    void roam();          // the functions below are explained in the operation.cpp file. 
    void servl();
    void servr();
    void servc();
    void level();
    void SETUP();
    void noINT();
    void IRread();
    void translateIR();
    void temp();
    void h2o();
    void measure();
};

extern operationclass operation;

#endif
