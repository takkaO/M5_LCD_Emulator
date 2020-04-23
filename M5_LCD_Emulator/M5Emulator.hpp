#pragma once

#include <iostream>
#include <cstdarg>
#include <bitset>
#include "TFTwrap/TFTemulator.hpp"

using namespace cv;



class Emu_M5_Display : public TFT_Emulator {
public:
	Emu_M5_Display();
	void updateDisplay(int delay_ms = 1);
	void begin(void);
	void sleep(void);
	void wakeup(void);
	void setBrightness(uint8_t brightness);
	void progressBar(int x, int y, int w, int h, uint8_t val);

protected:
	const int LCD_HEIGHT = 240;
	const int LCD_WIDTH = 320;
	bool is_sleep_mode = false;
};


class M5_Emulator {
public:
	Emu_M5_Display Lcd;

private:

};



extern M5_Emulator M5;
