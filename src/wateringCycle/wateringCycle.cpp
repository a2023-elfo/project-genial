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

void baisserBras(){//il faut l'integrer
    SERVO_Enable(0);
    for (int i = 0; i < 3; i++){
  
        SERVO_SetAngle(0, 130);
        delay(1000);
        SERVO_SetAngle(0, 40);
        delay(3000);
        SERVO_SetAngle(0, 130);
        delay(1000);
        Serial.println("BAISSE LE BRAS");       
    }
    SERVO_Disable(0);
};

void wateringCycleloop(int input){
     Serial.println("je suis dans arrosage");
    if(ROBUS_IsBumper(3)){
        *_outputWC = TROUVER_LIGNE;
    }    
};

// fonction exclusive