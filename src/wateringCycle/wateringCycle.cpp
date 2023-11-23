//#include <wateringCycle/waterinfCycle.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
//valeurs d'humidite
const int sec = 595;
const int humide = 239;


int* _outputWC = 0;
static const int DEMO_OLI = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void wateringCyclesetup(int* output){
    _outputWC = output;
    Serial.begin(9600);
};

void wateringCycleloop(int input){
    int valeurCapteur = analogRead(A13);

  int pourcentageHumidite = map(valeurCapteur, humide, sec, 100, 0);

   if (pourcentageHumidite >= 0 && pourcentageHumidite <= 100) 
   {
    Serial.print(pourcentageHumidite);
    Serial.println("%");
  } 
  
  else 
  {
    Serial.println("Erreur de lecture");
  }
  delay(1000); //delai d'une seconde avant la prochaine lecture  
};