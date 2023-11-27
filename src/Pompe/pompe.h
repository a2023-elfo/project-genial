#include <LibRobus.h>

class Pompe{
    private :
        int _pin;
        int _state;

    public :
        void setupPompe(uint8_t pin);
        void pompeOFF();
        void pompeON(int temps);
        int getStatePompe();
};