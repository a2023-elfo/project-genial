#ifndef theScreen_H_
#define theScreen_H_
#include <Arduino.h>
#include <LiquidCrystal.h>

// Exported theScreen functions to prevent bloat states that barely need it
class theScreen
{
    public :
        void theScreenSetup(String* firstLine, String* secondLine);
        void theScreenLoop();
        LiquidCrystal getLcd();

};


#endif //laisser a la fin 