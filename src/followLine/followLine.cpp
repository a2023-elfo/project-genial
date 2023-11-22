#include <followLine/followLine.h>
#include <lineFollower/lineFollower.h>
#include <rfid/rfid.h>
int* _outputFOL = 0;

static const int TROUVER_LIGNE = 0;
static const int SUIVRE_LIGNE = 1;
static const int TROUVER_POT = 2;
static const int ARROSER= 3;

char* allowedTags[] = {"0E008E974354", "0415148DE36B"};
Rfid r1(allowedTags[0], "Marguerite", 74.5);
Rfid r2(allowedTags[1], "Pissenlit", 20.76);
Rfid tags[] = {r1, r2};
int lecture = 0;

int numberofTags = sizeof(allowedTags)/sizeof(allowedTags[0]);
// fonction exporter 

void followLinesetup(int* output){
    _outputFOL = output;
    setupLineFollower();
};

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
      if (tagNumber > -1)
      {
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

    if (rfid_read() > -1)
    {
       *_outputFOL = TROUVER_POT;
    }

    if(ROBUS_IsBumper(3)){
        *_outputFOL = TROUVER_POT;
    }
};

// fonction exclusive