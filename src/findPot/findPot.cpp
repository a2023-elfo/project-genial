#include <findPot/findPot.h>

int* _outputFP = 0;
static const int TROUVER_LIGNE = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void findPotsetup(int* output){
    _outputFP = output;
};


void findPotloop(){
     Serial.println("je suis dans trouver pot");
    if(ROBUS_IsBumper(3)){
        *_outputFP = ARROSER;
    }    
};




// fonction exclusive