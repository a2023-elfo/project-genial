#include <Arduino.h>
#include <LibRobus.h>
#include <findPot/findPot.h>
#include <followLine/followLine.h>
#include <wateringCycle/waterinfCycle.h>
#include <DEMO_OLI/demoOli.h>

static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
static const int DEMO_OLI = 0;
int output = SUIVRE_LIGNE;

void setup() {
  BoardInit();
  Serial.begin(9600);
  Serial.println("Hello World!");
  findPotsetup(&output);
  followLinesetup(&output);
  wateringCyclesetup(&output);
  DEMOsetup(&output);
}

void loop() {

  if(ROBUS_IsBumper(0)){
      output = DEMO_OLI;
  } 
  if(ROBUS_IsBumper(2)){
      output = SUIVRE_LIGNE;
  }
  if(ROBUS_IsBumper(1)){
      output = TROUVER_POT;
  }

  if(output == SUIVRE_LIGNE){
    followLineloop();
  }
  else if(output == TROUVER_POT){
    findPotloop();
  }
  else if(output == ARROSER){
    wateringCycleloop(output);
  }
  else if(output == DEMO_OLI){
    DEMOloop();
  }
}
