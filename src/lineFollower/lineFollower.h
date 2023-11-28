
#ifndef lineFollower_H_
#define lineFollower_H_
#include <QTRSensors.h>

// Exported lineFollower functions to prevent bloat in the followLine state
void setupLineFollower();
void avance();
void peu_droite();
void peu_gauche();
void very_droite();
void very_gauche();
void stop(); 
void whiteLineLoop();
void blackLineLoop();

#endif //laisser a la fin 

