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
    MOTOR_SetSpeed(RIGHT,0.3);
    MOTOR_SetSpeed(LEFT,0.3);
};

void peu_droite(){ //le robot doit corriger sa trajectoire en allant un peu vers la droite
    MOTOR_SetSpeed(RIGHT,0.27);
    MOTOR_SetSpeed(LEFT,0.30);
}

void peu_gauche(){
    MOTOR_SetSpeed(RIGHT,0.30);
    MOTOR_SetSpeed(LEFT,0.27);
}

void very_droite(){
    MOTOR_SetSpeed(RIGHT,0.05);
    MOTOR_SetSpeed(LEFT,0.20);
}

void very_gauche(){
    MOTOR_SetSpeed(RIGHT,0.20);
    MOTOR_SetSpeed(LEFT,0.05);
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

void whiteLineLoop(){
    qtr.read(sensorValues);

    if(Compteur360deg == 0){
        ENCODER_Reset(RIGHT);
    }

    if (sensorValues[3] < 450 || sensorValues[4] < 450) // 2 capteurs du centre détectent ligne
    {
        avance();
        stopLoop = false;
        Compteur360deg = 0;
    }
    else if (sensorValues[5] < 500 || sensorValues[6] < 500) // si robot un peu trop à droite
    {
        peu_gauche();
        stopLoop = false;
        Compteur360deg = 0;
    }
    else if (sensorValues[1] < 500 || sensorValues[2] < 500 ) // si robot un peu trop à gauche
    {
        peu_droite();
        stopLoop = false;
        Compteur360deg = 0;
    }
    else if (sensorValues[7] < 600) // si robot bcp trop à droite
    {
        very_gauche();
        stopLoop = false;
        Compteur360deg = 0;
    }
    else if (sensorValues[0] < 600) // si robot bcp trop à gauche
    {
        very_droite();
        stopLoop = false;
        Compteur360deg = 0;
    }
    else if (sensorValues[1] < 600 && sensorValues[2] < 600  && sensorValues[3] < 600 && sensorValues[4] < 600  && sensorValues[5] < 600 && sensorValues[6] < 600  && sensorValues[7] < 600 && sensorValues[0] < 600) // si robot ne détecte pas de ligne
    {
        //Code de Mathieu pour qu'il fasse un tour et trouve la ligne
        Tour360Horaire();
    } else if (false) {
        // TODO mettre RFID() ici
    }
}

void blackLineLoop(){
    qtr.read(sensorValues);

    for (uint8_t i = 0; i < SensorCount; i++)
    {
        Serial.print(sensorValues[i]);
        Serial.print('\t');
    }
    Serial.println();

    if (sensorValues[3] > 500 || sensorValues[4] > 500) // 2 capteurs du centre détectent ligne
    {
        avance();
        stopLoop = false;
        Compteur360deg = 0;
    } 
    else if (sensorValues[5] > 600 || sensorValues[6] > 600) // si robot un peu trop à droite
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
    else if (sensorValues[1] < 500 && sensorValues[2] < 500  && sensorValues[3] < 500 && sensorValues[4] < 500  && sensorValues[5] < 500 && sensorValues[6] < 500  && sensorValues[7] < 500 && sensorValues[0] < 500) // si robot ne détecte pas de ligne
    {
        //Code de Mathieu pour qu'il fasse un tour et trouve la ligne
        Tour360Horaire();
        Serial.println("inloop");
    } else if (false) {
        // TODO mettre RFID() ici
    }
}
