#ifndef RFID_h
#define RFID_h  //create our header file



class RFIDclass   //setup the operation class
{

public:
    RFIDclass();

    void RFIDsetup();
    bool RFID_challenge();
    
};

extern RFIDclass RFID;

#endif
