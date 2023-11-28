#include <findPot/findPot.h>
#include <theScreen/theScreen.h>

int* _outputFP = 0;
int not_found = 0;
uint16_t distance = 0;
int encoderChanges = 0;
int currentEncoderValue = 0;
int* _DistanceAReculer = 0;
static const int DEMO_OLI = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;
// fonction exporter 
String* potFirstLine;
String* potSecondLine;
theScreen potScreen;

void findPotsetup(int* output, int* DistanceRecule, String* firstLine, String* secondLine){
    _outputFP = output;
    _DistanceAReculer = DistanceRecule;
    potFirstLine = firstLine;
    potSecondLine = secondLine;

    potScreen.theScreenSetup(potFirstLine, potSecondLine);
};

void findPotloop()
{
    *potFirstLine = "je checher le pot";
    *potSecondLine = "ALLLOOOOOO";
    potScreen.theScreenLoop();

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
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);

    while (ROBUS_ReadIR(0) < 620)
    {
        MOTOR_SetSpeed(LEFT, 0.14);
        MOTOR_SetSpeed(RIGHT, 0.15);
        currentEncoderValue = ENCODER_Read(LEFT);
        if (ROBUS_ReadIR(0) < distance)
        {
            MOTOR_SetSpeed(LEFT, -0.15);
            MOTOR_SetSpeed(RIGHT, 0.15);

            if (ENCODER_Read(RIGHT) > 900)
            {
                while (ROBUS_ReadIR(0) < distance)
                {
                    MOTOR_SetSpeed(LEFT, 0.15);
                    MOTOR_SetSpeed(RIGHT, -0.15);
                }
            }
            encoderChanges = ENCODER_Read(LEFT) - currentEncoderValue;
        }  
    }
    while (ROBUS_ReadIR(0) > 400)
    {
        MOTOR_SetSpeed(LEFT, 0.1);
        MOTOR_SetSpeed(RIGHT, 0.1);
    }
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    //*_DistanceAReculer = currentEncoderValue;
    *_DistanceAReculer = (int)distance;
    not_found = 0;
    while (ROBUS_ReadIR(3) < 450)
    {
        MOTOR_SetSpeed(LEFT, -0.1);
        MOTOR_SetSpeed(RIGHT, 0.1);
    }
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    *_outputFP = ARROSER;
};
// fonction exclusive