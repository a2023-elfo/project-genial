#include <DEMO_OLI/demoOli.h>

int* _outputDEMO = 0;
int not_found = 0;
int distance = 0;
static const int DEMO_OLI = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void DEMOsetup(int* output){
    _outputDEMO = output;
};

void DEMOloop(){ 
        *_outputDEMO = TROUVER_POT;    
}