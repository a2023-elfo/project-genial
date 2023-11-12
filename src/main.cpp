#include <Arduino.h>
#include <LibRobus.h>
#include <findLine/findLine.h>
#include <findPot/findPot.h>
#include <followLine/followLine.h>
#include <wateringCycle/waterinfCycle.h>

int output = 0;

static const int TROUVER_LIGNE = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;

void setup() {
  BoardInit();
  Serial.begin(9600);
  Serial.println("Hello World!");
  findLinesetup(&output);
  findPotsetup(&output);
  followLinesetup(&output);
  wateringCyclesetup(&output);
}

void loop() {
  delay(2000);
  if(output == TROUVER_LIGNE){
    findLineloop();
  }
  else if(output == SUIVRE_LIGNE){
    followLineloop();
  }
  else if(output == TROUVER_POT){
    findPotloop();
  }
  else if(output == ARROSER){
    wateringCycleloop(output);
  }

  
}
