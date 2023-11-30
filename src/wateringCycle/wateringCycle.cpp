#include <wateringCycle/wateringCycle.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <LibRobus.h>
#include <pompe/pompe.h>
#include <theScreen/theScreen.h>
#include <followLine/followLine.h>

//valeurs d'humidite
const int sec = 750;
const int humide = 275;

int* _outputWC = 0;
float* _wateredPlantHumidity = 0;
String* _wateredPlantName = 0;
String* _waterFirstLine = 0;
String* _waterSecondLine = 0;
int* _DistanceRecule = 0;
static const int DEMO_OLI = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
theScreen waterScreen;
// fonction exporter 

void wateringCycleSetup(int* output, String* wateredPlantName, float* wateredPlantHumidity, int* DistanceRecule2, String* firstLine, String* secondLine){
    _outputWC = output;
    _wateredPlantHumidity = wateredPlantHumidity;
    _wateredPlantName = wateredPlantName;
    _waterFirstLine = firstLine;
    _waterSecondLine = secondLine;
    _DistanceRecule = DistanceRecule2;

    waterScreen.theScreenSetup( _waterFirstLine, _waterSecondLine);
};

// Function to display the percentage on the second line, starting at the offset
void displayPercentage(int start, int percentage) {
  if (percentage > 100) {
    percentage = 100;
  } else if (percentage < 0) {
    percentage = 0;
  }

  if (percentage < 10) {
    waterScreen.getLcd().print(" ");
  }
  if (percentage < 100) {
    waterScreen.getLcd().print(" ");
  }
  waterScreen.getLcd().print(percentage);
  waterScreen.getLcd().print("%");
}

// "Manually" update the screen for custom formatting
void updateScreen(int readMoisture) {
  // Wipe LCD to start fresh
  LiquidCrystal lcd = waterScreen.getLcd();
  // "Begin" again to prevent writing nowhere
  lcd.begin(16, 2);

  // Get plantName length to center in the display
  int spaces = (16 - _wateredPlantName->length()) / 2;
  Serial.println(spaces);
  lcd.setCursor(spaces, 0);
  lcd.print(*_wateredPlantName);

  // Display expected soil moisture
  lcd.setCursor(0, 1);
  lcd.print("A:");
  displayPercentage(2, (int) *_wateredPlantHumidity);

  // Display read soil moisture
  lcd.setCursor(10, 1);
  lcd.print("L:");
  displayPercentage(12, readMoisture);
}

void monterBras(){
    SERVO_Enable(0);
    SERVO_SetAngle(0, 130);
    delay(1000);
    SERVO_Disable(0);
}

void baisserBras(){
    SERVO_Enable(0);
    SERVO_SetAngle(0, 30);
    delay(500);
    SERVO_Disable(0);
}

void Arroser(){
    Pompe pompe;
    pompe.setupPompe(45);
    pompe.pompeON(2);
    pompe.pompeOFF();
}

void wateringCycleloop(int input){
    *_waterFirstLine = " Cycle d'arrosage";
    *_waterSecondLine = "   en cours ";
    waterScreen.theScreenLoop();
    baisserBras();
    delay(5000);
    int valeurCapteur = analogRead(A13);
    Serial.println(valeurCapteur);
    int pourcentageHumidite = map(valeurCapteur, humide, sec, 100, 0);
    updateScreen(pourcentageHumidite);
    monterBras();

    if (pourcentageHumidite >= 0 && pourcentageHumidite <= 100) 
    {
        if (pourcentageHumidite < *_wateredPlantHumidity)
        {
            Arroser();
        }
    }
    else 
    {
      Serial.println("Erreur de lecture");
    }
    monterBras();
    ENCODER_Reset(LEFT);
    while (abs(ENCODER_Read(LEFT)) < *_DistanceRecule)
    {
      MOTOR_SetSpeed(LEFT, -0.15);
      MOTOR_SetSpeed(RIGHT, -0.15);
    }
    ENCODER_Reset(LEFT);
    while (ENCODER_Read(LEFT) < 1900)
    {
      MOTOR_SetSpeed(LEFT, 0.15);
      MOTOR_SetSpeed(RIGHT, -0.15);
    }
    *_outputWC = SUIVRE_LIGNE;
};