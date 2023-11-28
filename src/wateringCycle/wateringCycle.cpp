#include <wateringCycle/wateringCycle.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <LibRobus.h>
#include <pompe/pompe.h>
#include <theScreen/theScreen.h>

//valeurs d'humidite
const int sec = 595;
const int humide = 239;

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
    delay(800);
    SERVO_Disable(0);
}

void baisserBras(){
    SERVO_Enable(0);
    SERVO_SetAngle(0, 130);
    delay(500);
    SERVO_SetAngle(0, 40);
    delay(500);
    SERVO_Disable(0);
}

void Arroser(){
    Pompe pompe;
    pompe.setupPompe(45);
    pompe.pompeON(1.5);
    pompe.pompeOFF();
}

void wateringCycleloop(int input){
    *_waterFirstLine = " Watering cycle";
    *_waterSecondLine = "   in progress";
    waterScreen.theScreenLoop();
    baisserBras();
    delay(3000);
    int valeurCapteur = analogRead(A13);
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
    while (ROBUS_ReadIR(0) > *_DistanceRecule)
    {
        MOTOR_SetSpeed(LEFT, -0.14);
        MOTOR_SetSpeed(RIGHT, -0.15);
    }
    *_outputWC = SUIVRE_LIGNE;
};