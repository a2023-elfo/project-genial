#include <Pompe/pompe.h>

void Pompe::setupPompe(uint8_t pin){
    this->_pin = pin;
    this->_state = LOW;
    pinMode(_pin, OUTPUT);
}

void Pompe::pompeOFF(){
    _state = LOW;
    digitalWrite(this->_pin, LOW);
}

void Pompe::pompeON(int temps){
    _state = HIGH;
    unsigned long startMillis = millis();
    unsigned long interval = temps * 1000;
    while ((millis() - startMillis) <= interval)
    {
        digitalWrite(this->_pin, HIGH);
    }
    digitalWrite(this->_pin, LOW);
}

int Pompe::getStatePompe(){
    return this->_state;
}
