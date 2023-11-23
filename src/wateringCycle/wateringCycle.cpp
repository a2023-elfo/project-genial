#include <wateringCycle/waterinfCycle.h>

int* _outputWC = 0;
float* _rfidValue2 = 0;
int* _DistanceRecule = 0;
static const int DEMO_OLI = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void wateringCyclesetup(int* output, float* rfidValue, int* _DistanceRecule){
    _outputWC = output;
    _rfidValue2 = rfidValue;
    _DistanceRecule = _DistanceRecule;
};

void wateringCycleloop(int input){
     Serial.println("je suis dans arrosage");
    if(ROBUS_IsBumper(3)){
        *_outputWC = DEMO_OLI;
    }    
};

// fonction exclusive