#include <findPot/findPot.h>

int* _outputFP = 0;
int not_found = 0;
int virage;
int avancer;
static const int TROUVER_LIGNE = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void findPotsetup(int* output){
    _outputFP = output;
};

void findPotloop()
{
    Serial.println("je suis dans trouver pot");
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);

    while (ROBUS_ReadIR(0) < 200)
    {
        if (ENCODER_Read(RIGHT) > 2500)
        {
            not_found = 1;
            break;
        }
        MOTOR_SetSpeed(LEFT, -0.15);
        MOTOR_SetSpeed(RIGHT, 0.15);
    }
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    delay(200);
    if (not_found == 1)
    {
        ENCODER_Reset(LEFT);
        while (ENCODER_Read(LEFT) < 2500)
        {
            MOTOR_SetSpeed(LEFT, 0.2);
            MOTOR_SetSpeed(RIGHT, -0.2);
        }
        ENCODER_Reset(LEFT);
        while (ROBUS_ReadIR(0) < 200)
        {
            MOTOR_SetSpeed(LEFT, 0.15);
            MOTOR_SetSpeed(RIGHT, -0.15);
        }
        virage = ENCODER_ReadReset(LEFT);
        MOTOR_SetSpeed(LEFT, 0);
        MOTOR_SetSpeed(RIGHT, 0);
        delay(100);
    }
    else
    {
        virage = ENCODER_ReadReset(RIGHT);
    }
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    delay(200);
    ENCODER_Reset(LEFT);

    while (ROBUS_ReadIR(0) < 575)
    {
        MOTOR_SetSpeed(LEFT, 0.2);
        MOTOR_SetSpeed(RIGHT, 0.2);
    }
    avancer = ENCODER_ReadReset(LEFT);
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    delay(3000);

    while (ENCODER_Read(LEFT) != -avancer)
    {
        MOTOR_SetSpeed(LEFT, -0.2);
        MOTOR_SetSpeed(RIGHT, -0.2);
    }
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);

    if (not_found == 0)
    {
        while (ENCODER_Read(LEFT) != virage)
        {
            MOTOR_SetSpeed(LEFT, 0.15);
            MOTOR_SetSpeed(RIGHT, -0.15);
        }
    }
    else
    {
        while (ENCODER_Read(RIGHT) != virage)
        {
            MOTOR_SetSpeed(LEFT, -0.15);
            MOTOR_SetSpeed(RIGHT, 0.15);
        }
    }
    not_found = 0;
    *_outputFP = ARROSER;
};
// fonction exclusive