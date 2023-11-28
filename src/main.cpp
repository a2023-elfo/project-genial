#include <Arduino.h>
#include <LibRobus.h>
#include <findPot/findPot.h>
#include <followLine/followLine.h>
#include <wateringCycle/wateringCycle.h>
#include <DEMO_OLI/demoOli.h>
#include <RFID/RFID.h>
#include <pompe/pompe.h>
#include <theScreen/theScreen.h>

static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
static const int DEMO_OLI = 0;
int output = SUIVRE_LIGNE;
Pompe pompe;
theScreen screen;
String firstLine =  " 0            0 ";
String secondLine = "     |____|     ";
bool allumer = false;
float rfidValue = 0;
int distanceRecule = 0;

void setup() {
  BoardInit();
  Serial.begin(9600);
  findPotsetup(&output, &distanceRecule, &firstLine, &secondLine);
  screen.theScreenSetup(&firstLine, &secondLine);
  followLinesetup(&output, &rfidValue, &firstLine, &secondLine);
  wateringCyclesetup(&output, &rfidValue, &distanceRecule);
  DEMOsetup(&output);
  pompe.setupPompe(45);
}

void loop() {
    screen.theScreenLoop();
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
    firstLine = "En attente";
    secondLine = "   zzzzzzzzzz  ";
    MOTOR_SetSpeed(RIGHT, 0);
    MOTOR_SetSpeed(LEFT, 0);
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
    output = SUIVRE_LIGNE;
  }
}
