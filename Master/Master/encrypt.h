#ifndef encrypt_h
#define encrypt_h  //create our header file



class encryptclass   //setup the encryption class
{

public:
    encryptclass();
void rot(int inByte);  // this is the rotation 13 encryption function. 
void SETUP();


};

extern encryptclass encrypt;

#endif
