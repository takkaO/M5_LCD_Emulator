#include "M5Emulator.hpp"

using namespace cv;
using namespace std;

Emu_M5_Display::Emu_M5_Display() {
	_width = LCD_WIDTH;
	_height = LCD_HEIGHT;

	// Make canvas
	img = Mat::zeros(Size(_width, _height), CV_8UC3);
}

void Emu_M5_Display::updateDisplay(int delay_ms) {
	if (is_sleep_mode == false) {
		imshow("M5Stack LCD Emulator", img);
	}
	else {
		Mat _img = Mat::zeros(Size(LCD_WIDTH, LCD_HEIGHT), CV_8UC3);
		imshow("M5Stack LCD Emulator", _img);
	}
	waitKey(delay_ms);
}

void Emu_M5_Display::begin(void) {
	// dummy function
	cout << "M5Stack ready!" << endl;
}

void Emu_M5_Display::sleep(void) {
	is_sleep_mode = true;
}

void Emu_M5_Display::wakeup(void) {
	is_sleep_mode = false;
}

void Emu_M5_Display::setBrightness(uint8_t brightness) {
	/* No implemented now! */
	cout << "\"setBrightness\" is NOT yet implemented!" << endl;
}

void Emu_M5_Display::progressBar(int x, int y, int w, int h, uint8_t val) {
	/* No implemented now! */
	cout << "\"progressBar\" is NOT yet implemented!" << endl;
}


/* Declaration M5 object */
M5_Emulator M5;