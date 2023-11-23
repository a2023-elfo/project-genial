#include <lineFollower/lineFollower.h>
#include <Arduino.h>
#include <LibRobus.h>
QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
uint16_t sensors[8];
int Compteur360deg = 0;
bool stopLoop = false;
void setupLineFollower(){
    BoardInit();
    Serial.begin(9600);
    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A1, A2, A3, A4, A5, A6, A7, A8}, SensorCount);
};

void avance(){
    MOTOR_SetSpeed(RIGHT,0.25);
    MOTOR_SetSpeed(LEFT,0.25);
};

void peu_droite(){ //le robot doit corriger sa trajectoire en allant un peu vers la droite
    MOTOR_SetSpeed(RIGHT,0.22);
    MOTOR_SetSpeed(LEFT,0.25);
}

void peu_gauche(){
    MOTOR_SetSpeed(RIGHT,0.25);
    MOTOR_SetSpeed(LEFT,0.22);
}

void very_droite(){
    MOTOR_SetSpeed(RIGHT,-0.05);
    MOTOR_SetSpeed(LEFT,0.20);
}

void very_gauche(){
    MOTOR_SetSpeed(RIGHT,0.20);
    MOTOR_SetSpeed(LEFT,-0.05);
}

void Tour360Horaire(){
    
    if(!stopLoop){
        Compteur360deg = abs(ENCODER_Read(RIGHT));
        if(Compteur360deg< 7893 ){     //d = 7.4  pi*7.4 = 23.247  d roue = 3  pi*3 = 9.42   23.247/ 9.42 = 2.47    2.47 * 3200 = 7893
            MOTOR_SetSpeed(RIGHT,-0.20);
            MOTOR_SetSpeed(LEFT,0.20);
        }else{
            stopLoop = true;
            ENCODER_Reset(RIGHT);
        }
    }else{
        stop();
        if(Compteur360deg == 0){
            stopLoop = false;
        }
    }
}

void Tour360AntiHoraire(){
    if(!stopLoop){
        Compteur360deg = ENCODER_Read(RIGHT);
        if(Compteur360deg< 7893 ){     //d = 7.4  pi*7.4 = 23.247  d roue = 3  pi*3 = 9.42   23.247/ 9.42 = 2.47    2.47 * 3200 = 7893
            MOTOR_SetSpeed(RIGHT,0.20);
            MOTOR_SetSpeed(LEFT,-0.20);
        }else{
            stopLoop = true;
            ENCODER_Reset(RIGHT);
        }
    }else{
        stop();
        ENCODER_Reset(RIGHT);
    }
}

void stop(){
    MOTOR_SetSpeed(RIGHT,0);
    MOTOR_SetSpeed(LEFT,0);
}

void blackLineLoop(){
    qtr.read(sensorValues);

    for (uint8_t i = 0; i < SensorCount; i++)
    {
        Serial.print(sensorValues[i]);
        Serial.print('\t');
    }
    Serial.println();

    
    if (sensorValues[5] > 600 || sensorValues[6] > 600) // si robot un peu trop à droite
    {
        peu_gauche();
        stopLoop = false;
        Compteur360deg = 0;
    }
    else if (sensorValues[1] > 600 || sensorValues[2] > 600 ) // si robot un peu trop à gauche
    {
        peu_droite();
        stopLoop = false;
        Compteur360deg = 0;
    }
    else if (sensorValues[7] > 700 ) // si robot bcp trop à droite
    {
        very_gauche();
        stopLoop = false;
        Compteur360deg = 0;
    }
    else if (sensorValues[0] > 700 ) // si robot bcp trop à gauche
    {
        very_droite();
        stopLoop = false;
        Compteur360deg = 0;
    }

    else if (sensorValues[1] > 500 && sensorValues[0] > 600 && sensorValues[6] < 400 && sensorValues[7] < 400) // doit tourner 90 droite
    {
        very_droite();
        stopLoop = false;
        Compteur360deg = 0;
    } 
    else if (sensorValues[6] > 500 && sensorValues[7] > 600 && sensorValues[0] < 400 && sensorValues[1] < 400) // doit tourner 90 gauche
    {
        very_gauche();
        stopLoop = false;
        Compteur360deg = 0;
    } 
    else if (sensorValues[3] > 500 || sensorValues[4] > 500) // 2 capteurs du centre détectent ligne
    {
        avance();
        stopLoop = false;
        Compteur360deg = 0;
    } 
/*
    else if (sensorValues[1] < 500 && sensorValues[2] < 500  && sensorValues[3] < 500 && sensorValues[4] < 500  && sensorValues[5] < 500 && sensorValues[6] < 500  && sensorValues[7] < 500 && sensorValues[0] < 500) // si robot ne détecte pas de ligne
    {
        //Code de Mathieu pour qu'il fasse un tour et trouve la ligne
        Tour360Horaire();
        Serial.println("inloop");
    } */
}
