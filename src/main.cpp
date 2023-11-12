#include <Arduino.h>
#include <LibRobus.h>
#include <findLine/findLine.h>
#include <findPot/findPot.h>
#include <followLine/followLine.h>
#include <wateringCycle/waterinfCycle.h>

void setup() {
  BoardInit();
  Serial.begin(9600);
  Serial.println("Hello World!");
}

void loop() {
  
  
}
