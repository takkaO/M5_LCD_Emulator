#include "M5Stack.h"

using namespace std;

void delay(unsigned int ms) {
	M5.Lcd.updateDisplay();
	Sleep(ms);
}