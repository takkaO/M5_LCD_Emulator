#include "main.hpp"


/* M5Stack CODE BEGIN */
#include "M5Stack.h"

void setup() {
	for (int i = 0; i < COLORS_NUM; i++) {
		M5.Lcd.fillScreen(COLORS[i]);
		delay(1000);
	}
	M5.Lcd.fillScreen(BLACK);
	M5.Lcd.drawString("Hello World!", 0, 0, 1);
	M5.Lcd.setCursor(0, 15);
	M5.Lcd.setTextSize(2);
	M5.Lcd.drawString("Hello World!", 100, 100, 1);

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