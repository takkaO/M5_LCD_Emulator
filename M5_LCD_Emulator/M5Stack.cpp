#include "M5Stack.h"


void delay(unsigned int ms) {
	M5.Lcd.updateDisplay();
	Sleep(ms);
}


#ifdef DEV
void font_test() {
	uint8_t column[6];
	uint8_t c = 49;
	for (int i = 0; i < 5; i++)
	{
		column[i] = font[(c * 5) + i];
	}
	column[5] = 0;

	uint8_t mask = 0x1;
	uint8_t res;
	for (int i = 0; i < 5; i++) {
		mask = 0x1;
		for (int k = 0; k < 8; k++) {
			res = column[i] & mask;
			if (res != 0) {
				cout << 1;
			}
			else {
				cout << "0";
			}
			mask <<= 1;
		}
		cout << endl;
	}
}
#endif
