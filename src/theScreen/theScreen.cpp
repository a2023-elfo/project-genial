#include <theScreen/theScreen.h>
#include <Arduino.h>

const int rs = 22, en = 24, d4 = 42, d5 = 43, d6 = 44, d7 = 45;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String *_firstLine = 0;
String *_secondLine = 0;
String latestDisplayValue;

void theScreen::theScreenSetup(String *firstLine, String *secondLine)
{
    _firstLine = firstLine;
    _secondLine = secondLine;

    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print(*firstLine);
    lcd.setCursor(0, 1);
    lcd.print(*secondLine);
}

void theScreen::theScreenLoop() {
    String currentLine = *_firstLine + *_secondLine;
    if (currentLine != latestDisplayValue) {
        latestDisplayValue = currentLine;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(*_firstLine);
        lcd.setCursor(0, 1);
        lcd.print(*_secondLine);
    }
}