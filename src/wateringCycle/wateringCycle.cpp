#include <wateringCycle/waterinfCycle.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <LibRobus.h>
#include <pompe/pompe.h>

//valeurs d'humidite
const int sec = 595;
const int humide = 239;

int* _outputWC = 0;
float* _rfidValue2 = 0;
int* _DistanceRecule = 0;
static const int DEMO_OLI = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void wateringCyclesetup(int* output, float* rfidValue, int* DistanceRecule2){
    _outputWC = output;
    Serial.begin(9600);
    _rfidValue2 = rfidValue;
    _DistanceRecule = DistanceRecule2;
};

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
    baisserBras();
    delay(3000);
    int valeurCapteur = analogRead(A13);
    int pourcentageHumidite = map(valeurCapteur, humide, sec, 100, 0);
    monterBras();

    if (pourcentageHumidite >= 0 && pourcentageHumidite <= 100) 
    {
        if (pourcentageHumidite < *_rfidValue2)
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