#include "main.hpp"


/* M5Stack CODE BEGIN */


void setup() {
	M5.Lcd.printf("Hello World!");
	M5.Lcd.setCursor(0, 15);
	M5.Lcd.setTextSize(2);
	M5.Lcd.printf("Hello World!");
}

void loop() {
	
}


/* M5Stack CODE END */



int main(void) {
	
	setup();
	M5.Lcd.updateDisplay();

	while (1) {
		loop();
		M5.Lcd.updateDisplay();
	}
}