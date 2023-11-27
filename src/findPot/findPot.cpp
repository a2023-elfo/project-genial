#include <findPot/findPot.h>

int* _outputFP = 0;
int not_found = 0;
int distance = 0;
int currentEncoderValue = 0;
int encoderChanges = 0;
int* _DistanceAReculer = 0;
static const int DEMO_OLI = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 

void findPotsetup(int* output, int* DistanceRecule){
    _outputFP = output;
    _DistanceAReculer = DistanceRecule;
};

void findPotloop()
{
    Serial.println("je suis dans trouver pot");
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);

    while (ROBUS_ReadIR(0) < 175)
    {
        if (ENCODER_Read(RIGHT) > 2500)
        {
            not_found = 1;
            break;
        }
        MOTOR_SetSpeed(LEFT, -0.15);
        MOTOR_SetSpeed(RIGHT, 0.15);
    }

    if (not_found == 1)
    {
        ENCODER_Reset(LEFT);
        while (ENCODER_Read(LEFT) < 2500)
        {
            MOTOR_SetSpeed(LEFT, 0.2);
            MOTOR_SetSpeed(RIGHT, -0.2);
        }

        while (ROBUS_ReadIR(0) < 175)
        {
            MOTOR_SetSpeed(LEFT, 0.15);
            MOTOR_SetSpeed(RIGHT, -0.15);
        }
    }
    
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    distance = ROBUS_ReadIR(0);
    delay(200);
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);

    while (ROBUS_ReadIR(0) < 575)
    {
        MOTOR_SetSpeed(LEFT, 0.15);
        MOTOR_SetSpeed(RIGHT, 0.15);
        currentEncoderValue = ENCODER_Read(RIGHT);

        while (ROBUS_ReadIR(0) < (distance - 25))
        {
            MOTOR_SetSpeed(LEFT, -0.15);
            MOTOR_SetSpeed(RIGHT, 0.15);
            
            if (ENCODER_Read(RIGHT) > 900)
            {
                while (ROBUS_ReadIR(0) < (distance - 25))
                {
                    MOTOR_SetSpeed(LEFT, 0.15);
                    MOTOR_SetSpeed(RIGHT, -0.15);
                }
            }
            encoderChanges = ENCODER_Read(RIGHT);
        }
    }
    *_DistanceAReculer = currentEncoderValue - encoderChanges;
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    not_found = 0;
    *_outputFP = ARROSER;
};
// fonction exclusive