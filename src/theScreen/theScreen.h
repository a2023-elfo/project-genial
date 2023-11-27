#ifndef theScreen_H_
#define theScreen_H_

#include <LiquidCrystal.h>

class theScreen
{
    public :
        void theScreenSetup(String* firstLine, String* secondLine);
        void theScreenLoop();
};


#endif //laisser a la fin 