#include <Arduino.h>
#include <LibRobus.h>
#include <findPot/findPot.h>
#include <followLine/followLine.h>
#include <wateringCycle/waterinfCycle.h>
#include <DEMO_OLI/demoOli.h>
#include <pompe/pompe.h>

static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
static const int DEMO_OLI = 0;
int output = SUIVRE_LIGNE;
Pompe pompe;
bool allumer = false;
float rfidValue = 0;
int distanceRecule = 0;

void setup() {
  BoardInit();
  Serial.begin(9600);
  findPotsetup(&output, &distanceRecule );
  followLinesetup(&output, &rfidValue);
  wateringCyclesetup(&output, &rfidValue, &distanceRecule);
  DEMOsetup(&output);
  pompe.setupPompe(45);
}

void loop() {
    if(digitalRead(48)==LOW){
      allumer=!allumer;
      delay(500);
    }
    if(allumer){

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
  } else {
    MOTOR_SetSpeed(RIGHT, 0);
    MOTOR_SetSpeed(LEFT, 0);
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
    output = SUIVRE_LIGNE;
  }
}
