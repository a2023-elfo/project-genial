#include <wateringCycle/waterinfCycle.h>

int* _outputWC = 0;
static const int TROUVER_LIGNE = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void wateringCyclesetup(int* output){
    _outputWC = output;
};


void wateringCycleloop(int input){
     Serial.println("je suis dans arrosage");
    if(ROBUS_IsBumper(3)){
        *_outputWC = TROUVER_LIGNE;
    }    
};




// fonction exclusive