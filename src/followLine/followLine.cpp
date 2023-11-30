#include <followLine/followLine.h>
#include <lineFollower/lineFollower.h>
#include <rfid/rfid.h>
int* _outputFOL = 0;
float* _readPlantHumidity = 0;
String* _readPlantName = 0;
static const int DEMO_OLI = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;

char* allowedTags[] = {"0E008E974354", "1600C3C98A96", "1600BF97BA84"};
Rfid r1(allowedTags[0], "Pissenlit", 70.0);
Rfid r2(allowedTags[1], "Cactus", 0.0);
Rfid r3(allowedTags[2], "Marguerite", 60.0);
Rfid tags[] = {r1, r2, r3};
int lecture = 0;

String* followLineFirstString;
String* followLineSecondString;

void followLineSetup(int* output, String* readPlantName, float* readPlantHumidity, String* firstLine, String* secondLine){
    _outputFOL = output;
    _readPlantHumidity = readPlantHumidity;
    _readPlantName = readPlantName;
    followLineFirstString = firstLine;
    followLineSecondString = secondLine;
    SERVO_Enable(0);
    SERVO_SetAngle(0, 130);
    delay(200);
    SERVO_Disable(0);
    setupLineFollower();
};

/*Compare le tag lu aux tags de la liste allowedTags
et retourne la position du tag dans la liste*/
int findTag(char tagValue[])
{
  for (int i = 0; i < sizeof(tags); i++)
  {
    if (strcmp(tagValue, tags[i].getTag()) == 0)
    {
      return i;
    }
  }
  return -1;
}

//La fonction lecture du rfid stocke les 12 caractères du tag lu dans un tableau 
int rfid_read()
{
  int valread = 0;
  char val;
  char rfidtag[13];
  int i = 0;
  int tagNumber = 0;

  if (Serial.available() > 0)
  {
    if ((val = Serial.read()) == 2)
    {
      while (valread < 12)
      {
        if (Serial.available() > 0)
        {
          val = Serial.read();
          if ((val == 0x0D) || (val == 0x0A) || (val == 0x03) || (val == 0x02))
          {
            break;
          }
          else
          {
            rfidtag[i] = val;
            i++;
          }
        }
      }
      rfidtag[i] = '\0';
      tagNumber = findTag(rfidtag);
      if (tagNumber > -1 && tags[tagNumber].getTauxHumidite() != *_readPlantHumidity)
      {
        *_readPlantHumidity = tags[tagNumber].getTauxHumidite();
        return tagNumber;
      }
      else
      {
        return -1;
      }
    }
  }
  return -1;
}

void followLineloop(){
    *followLineFirstString = "   Deplacement";
    *followLineSecondString = "    en cours";
    blackLineLoop();

    int tagNumber = rfid_read();

    if (tagNumber > -1)
    {
      *_readPlantHumidity = tags[tagNumber].getTauxHumidite();
      *_readPlantName = tags[tagNumber].getNomPlanteString();
      MOTOR_SetSpeed(LEFT, 0);
      MOTOR_SetSpeed(RIGHT, 0);
      SERVO_Enable(0);
      SERVO_SetAngle(0, 130);
      delay(500);
      SERVO_Disable(0);
      *_outputFOL = TROUVER_POT;
    }
    else
    {
      *_outputFOL = SUIVRE_LIGNE;
    }
};

// fonction exclusive