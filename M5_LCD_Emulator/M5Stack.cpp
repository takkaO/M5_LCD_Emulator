#include "M5Stack.h"

void delay(unsigned int ms) {
	M5.Lcd.updateDisplay();
	Sleep(ms);
}