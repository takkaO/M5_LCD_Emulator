#pragma once

#include <iostream>
#include <cstdarg>
#include <bitset>
#include <opencv2/opencv.hpp>
extern "C" {
	#include "fonts.h"
}

using namespace cv;


// from ILI9341_Defines.h
const uint16_t BLACK       = 0x0000;      /*   0,   0,   0 */
const uint16_t NAVY        = 0x000F;      /*   0,   0, 128 */
const uint16_t DARKGREEN   = 0x03E0;      /*   0, 128,   0 */
const uint16_t DARKCYAN    = 0x03EF;      /*   0, 128, 128 */
const uint16_t MAROON      = 0x7800;      /* 128,   0,   0 */
const uint16_t PURPLE      = 0x780F;      /* 128,   0, 128 */
const uint16_t OLIVE       = 0x7BE0;      /* 128, 128,   0 */
const uint16_t LIGHTGREY   = 0xC618;      /* 192, 192, 192 */
const uint16_t DARKGREY    = 0x7BEF;      /* 128, 128, 128 */
const uint16_t BLUE        = 0x001F;      /*   0,   0, 255 */
const uint16_t GREEN       = 0x07E0;      /*   0, 255,   0 */
const uint16_t CYAN        = 0x07FF;      /*   0, 255, 255 */
const uint16_t RED         = 0xF800;      /* 255,   0,   0 */
const uint16_t MAGENTA     = 0xF81F;      /* 255,   0, 255 */
const uint16_t YELLOW      = 0xFFE0;      /* 255, 255,   0 */
const uint16_t WHITE       = 0xFFFF;      /* 255, 255, 255 */
const uint16_t ORANGE      = 0xFD20;      /* 255, 165,   0 */
const uint16_t GREENYELLOW = 0xAFE5;      /* 173, 255,  47 */
const uint16_t PINK        = 0xF81F;

// from In_eSPI.h
const uint16_t TFT_BLACK       = BLACK;
const uint16_t TFT_NAVY        = NAVY;
const uint16_t TFT_DARKGREEN   = DARKGREEN;
const uint16_t TFT_DARKCYAN    = DARKCYAN;
const uint16_t TFT_MAROON      = MAROON;
const uint16_t TFT_PURPLE      = PURPLE;
const uint16_t TFT_OLIVE       = OLIVE;
const uint16_t TFT_LIGHTGREY   = LIGHTGREY;
const uint16_t TFT_DARKGREY    = DARKGREY;
const uint16_t TFT_BLUE        = BLUE;
const uint16_t TFT_GREEN       = GREEN;
const uint16_t TFT_CYAN        = CYAN;
const uint16_t TFT_RED         = RED;
const uint16_t TFT_MAGENTA     = MAGENTA;
const uint16_t TFT_YELLOW      = YELLOW;
const uint16_t TFT_WHITE       = WHITE;
const uint16_t TFT_ORANGE      = ORANGE;
const uint16_t TFT_GREENYELLOW = GREENYELLOW;
const uint16_t TFT_PINK        = PINK;

const uint16_t COLORS[] = { BLACK,NAVY, DARKGREEN, DARKCYAN, MAROON, 
                            PURPLE, OLIVE, LIGHTGREY, DARKGREY, BLUE,
	                        GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE, 
	                        ORANGE, GREENYELLOW, PINK };
const uint8_t COLORS_NUM = sizeof(COLORS) / sizeof(uint16_t);


class Emu_M5_Display {
public:
	Emu_M5_Display();
	void updateDisplay(int delay_ms = 1);
	void begin(void);
	void sleep(void);
	void wakeup(void);
	void setBrightness(uint8_t brightness);
	void progressBar(int x, int y, int w, int h, uint8_t val);
	uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
	void fillScreen(uint16_t color);
	void setTextColor(uint16_t color, uint16_t backgroundcolor = TFT_BLACK);
	void drawPixel(int16_t x, int16_t y, uint16_t color);
	void drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color = WHITE);
	void drawFastHLine(int32_t x, int32_t y, int32_t h, uint32_t color = WHITE);
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color = WHITE);
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color = WHITE);
	void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color = WHITE);
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color = WHITE);
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color = WHITE);
	void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color = WHITE);
	void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color = WHITE);
	void drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color = WHITE);
	void fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color = WHITE);
	void drawString(const char* str, int32_t poX, int32_t poY);
	void setTextSize(uint8_t size);
	void setCursor(uint16_t x, uint16_t y);
	void print(const char *fmt);
	void printf(const char *fmt, ...);
	void drawChar(int32_t x, int32_t y, uint16_t c, uint32_t color, uint32_t bg, uint32_t size);

private:
	Scalar convert16Int2Scalar(uint16_t color);
	uint32_t color16to24(uint16_t color565);	// use this
	Scalar transposeRGB2BGR(Scalar color);

	const int LCD_HEIGHT = 240;
	const int LCD_WIDTH = 320;
	uint16_t cursor_x = 0;
	uint16_t cursor_y = 0;
	double font_size = 0.3;
	uint16_t font_color = WHITE;
	uint16_t font_background_color = TFT_BLACK;
	bool is_sleep_mode = false;
	Mat img;
};


class M5_Emulator {
public:
	Emu_M5_Display Lcd;

private:

};



extern M5_Emulator M5;
