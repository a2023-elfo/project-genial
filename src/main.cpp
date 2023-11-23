#include <Arduino.h>
#include <LibRobus.h>
#include <findPot/findPot.h>
#include <followLine/followLine.h>
#include <wateringCycle/waterinfCycle.h>

static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;

int output = SUIVRE_LIGNE;

void setup() {
  BoardInit();
  Serial.begin(9600);
  Serial.println("Hello World!");
  findPotsetup(&output);
  followLinesetup(&output);
  wateringCyclesetup(&output);
}

void loop() {

  if(output == SUIVRE_LIGNE){
    followLineloop();
  }
  else if(output == TROUVER_POT){
    findPotloop();
  }
  else if(output == ARROSER){
    wateringCycleloop(output);
  }


}
