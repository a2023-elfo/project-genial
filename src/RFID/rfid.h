#ifndef rfid_H_
#define rfid_H_
#include <Arduino.h>
#include <string.h>

class Rfid
{
public :
    Rfid(char numtag[], char plante[], float humidite);
    ~Rfid();
    char* getTag();
    char* getNomPlante();
    String getNomPlanteString();
    String getTagString();
    float getTauxHumidite();

private :
    char tag[13];
    char nom_plante[30];
    float taux_humidite;
};

#endif