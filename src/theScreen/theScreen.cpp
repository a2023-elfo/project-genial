#include <theScreen/theScreen.h>
#include <LiquidCrystal.h>

const int rs = 22, en = 24, d4 = 26, d5 = 28, d6 = 30, d7 = 32;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String *_firstLine = 0;
String *_secondLine = 0;
String latestDisplayValue;

void theScreen::theScreenSetup(String *firstLine, String *secondLine)
{
    _firstLine = firstLine;
    _secondLine = secondLine;
}


void theScreen::theScreenLoop() {
    String currentValue = *_firstLine + *_secondLine;
    if (currentValue != latestDisplayValue) {
        // Necessary to begin every time, otherwise the screen is not updated
        lcd.begin(16, 2);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(*_firstLine);
        lcd.setCursor(0, 1);
        lcd.print(*_secondLine);
        latestDisplayValue = currentValue;
    } 
}

// Expose the lcd object for more specific manipulations
LiquidCrystal theScreen::getLcd() {
    return lcd;
}