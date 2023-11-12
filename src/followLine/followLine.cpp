#include <followLine/followLine.h>

int* _outputFOL = 0;

static const int TROUVER_LIGNE = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void followLinesetup(int* output){
    _outputFOL = output;
};


void followLineloop(){
     Serial.println("je suis dans suivre ligne");
    if(ROBUS_IsBumper(3)){
        *_outputFOL = TROUVER_POT;
    }    
};




// fonction exclusive