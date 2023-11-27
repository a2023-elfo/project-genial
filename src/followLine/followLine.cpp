#include <followLine/followLine.h>
#include <lineFollower/lineFollower.h>
#include <rfid/rfid.h>
int* _outputFOL = 0;
float* _rfidValue = 0;
static const int DEMO_OLI = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;

char* allowedTags[] = {"0E008E974354", "0415148DE36B"};
Rfid r1(allowedTags[0], "Marguerite", 74.5);
Rfid r2(allowedTags[1], "Pissenlit", 20.76);
Rfid tags[] = {r1, r2};
int lecture = 0;

int numberofTags = sizeof(allowedTags)/sizeof(allowedTags[0]);

void followLinesetup(int* output , float* rfidValue){
    _outputFOL = output;
    _rfidValue = rfidValue;
    setupLineFollower();
};

/*Compare le tag lu aux tags de la liste allowedTags
et retourne la position du tag dans la liste*/
int findTag(char tagValue[])
{
  for (int i = 0; i < numberofTags; i++)
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
      Serial.println(tagNumber);
      if (tagNumber > -1)
      {
        *_rfidValue = tags[tagNumber].getTauxHumidite();
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
    blackLineLoop();

    //Il faudrait aussi une variable pour stocker le taux d'humidité associé
    //à la chip RFID qui vient d'être lu
    if (rfid_read() > -1)
    {
      MOTOR_SetSpeed(LEFT, 0);
      MOTOR_SetSpeed(RIGHT, 0);
       *_outputFOL = TROUVER_POT;
    }
};

// fonction exclusive