#include "main.hpp"

void setup() {
	M5.Lcd.printf("Hello World!");
	M5.Lcd.setCursor(0, 15);
	M5.Lcd.setTextSize(2);
	M5.Lcd.printf("Hello World!");
}

void loop() {
	
}


int main(void) {
	
	setup();
	M5.Lcd.updateDisplay();

	while (1) {
		loop();
		M5.Lcd.updateDisplay();
	}
}