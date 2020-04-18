#include "M5Stack.h"

#ifdef LINUX
#include <unistd.h>
#define Sleep(x) usleep(1000*(x))
#endif

void delay(unsigned int ms) {
	M5.Lcd.updateDisplay();
	Sleep(ms);
}
