#pragma once

#include <iostream>
#include <cstdarg>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;


// from ILI9341_Defines.h
const Scalar BLACK		 = Scalar(0, 0, 0);
const Scalar NAVY		 = Scalar(128, 0, 0);
const Scalar DARKGREEN	 = Scalar(0, 128, 0);
const Scalar MAROON		 = Scalar(0, 0, 128);
const Scalar PURPLE		 = Scalar(128, 0, 128);
const Scalar OLIVE		 = Scalar(0, 128, 128);
const Scalar LIGHTGREY	 = Scalar(192, 192, 192);
const Scalar BLUE		 = Scalar(255, 0, 0);
const Scalar GREENYELLOW = Scalar(47, 255, 173);
const Scalar GREEN		 = Scalar(0, 255, 0);
const Scalar YELLOW		 = Scalar(0, 255, 255);
const Scalar ORANGE		 = Scalar(0, 165, 255);
const Scalar PINK		 = Scalar(203, 192, 255);
const Scalar CYAN		 = Scalar(255, 255, 0);
const Scalar DARKCYAN	 = Scalar(128, 128, 0);
const Scalar RED		 = Scalar(0, 0, 255);
const Scalar MAGENTA	 = Scalar(255, 0, 255);
const Scalar WHITE		 = Scalar(255, 255, 255);

class Emu_M5_Display {
public:
	Emu_M5_Display();
	void updateDisplay(int delay_ms = 1);
	void fillScreen(Scalar color);
	void drawPixel(int16_t x, int16_t y, Scalar color);
	void drawFastVLine(int32_t x, int32_t y, int32_t h, Scalar color = WHITE);
	void drawFastHLine(int32_t x, int32_t y, int32_t h, Scalar color = WHITE);
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, Scalar color = WHITE);
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, Scalar color = WHITE);
	void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, Scalar color = WHITE);
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, Scalar color = WHITE);
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Scalar color = WHITE);
	void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, Scalar color = WHITE);
	void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, Scalar color = WHITE);
	void drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, Scalar color = WHITE);
	void fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, Scalar color = WHITE);
	void drawString(const char* str, int32_t poX, int32_t poY);
	void setTextSize(uint8_t size);
	void setCursor(uint16_t x, uint16_t y);
	void printf(const char* fmt, ...);

private:
	const int LCD_HEIGHT = 240;
	const int LCD_WIDTH = 320;
	uint16_t cursor_x = 0;
	uint16_t cursor_y = 0;
	double font_size = 0.3;
	int str_display_offset = 10;
	Mat img;
};


class M5_Emulator {
public:
	Emu_M5_Display Lcd;

private:

};



extern M5_Emulator M5;