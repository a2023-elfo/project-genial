#include <findLine/findLine.h>


int* _outputFL = 0;
static const int TROUVER_LIGNE = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void findLinesetup(int* output){
    _outputFL = output;
};


void findLineloop(){
    Serial.println("je suis dans trouver ligne");
    if(ROBUS_IsBumper(3)){
        *_outputFL = SUIVRE_LIGNE;
    }    
};



// fonction exclusive