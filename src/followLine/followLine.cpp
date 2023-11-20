#include <followLine/followLine.h>
#include <lineFollower/lineFollower.h>

int* _outputFOL = 0;

static const int TROUVER_LIGNE = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void followLinesetup(int* output){
    _outputFOL = output;
    setupLineFollower();
};


void followLineloop(){
    blackLineLoop();
    if(ROBUS_IsBumper(3)){
        *_outputFOL = TROUVER_POT;
    }    
};




// fonction exclusive