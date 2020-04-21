#include "M5Emulator.hpp"

using namespace cv;
using namespace std;

Emu_M5_Display::Emu_M5_Display() {
	// Make canvas
	img = Mat::zeros(Size(LCD_WIDTH, LCD_HEIGHT), CV_8UC3);

	// set font parameters
	textsize = 1;
	textdatum = TL_DATUM;
	cursor_x = 0;
	cursor_y = 0;
	padX = 0;     // No padding
}

void Emu_M5_Display::updateDisplay(int delay_ms) {
	if (is_sleep_mode == false) {
		imshow("M5Stack Emulator", img);
	}
	else {
		Mat _img = Mat::zeros(Size(LCD_WIDTH, LCD_HEIGHT), CV_8UC3);
		imshow("M5Stack Emulator", _img);
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

uint16_t Emu_M5_Display::color565(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

uint32_t Emu_M5_Display::color16to24(uint16_t color565) {
	uint8_t r = (color565 >> 8) & 0xF8; r |= (r >> 5);
	uint8_t g = (color565 >> 3) & 0xFC; g |= (g >> 6);
	uint8_t b = (color565 << 3) & 0xF8; b |= (b >> 5);

	return ((uint32_t)r << 16) | ((uint32_t)g << 8) | ((uint32_t)b << 0);
}

void Emu_M5_Display::fillScreen(uint16_t color) {
	Point pt1 = Point(0, 0);
	Point pt2 = Point(LCD_WIDTH, LCD_HEIGHT);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));
	rectangle(img, pt1, pt2, _color, FILLED);
}

void Emu_M5_Display::setTextColor(uint16_t color, uint16_t backgroundcolor) {
	font_color = color;
	font_background_color = backgroundcolor;
}

void Emu_M5_Display::drawPixel(int16_t x, int16_t y, uint16_t color) {
	Point pt1 = Point(x, y);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));
	line(img, pt1, pt1, _color, 1);
}

void Emu_M5_Display::drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color) {
	Point pt1 = Point(x, y);
	Point pt2 = Point(x, y + h);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));
	line(img, pt1, pt2, _color, 1);
}

void Emu_M5_Display::drawFastHLine(int32_t x, int32_t y, int32_t h, uint32_t color) {
	Point pt1 = Point(x, y);
	Point pt2 = Point(x + h, y);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));
	line(img, pt1, pt2, _color, 1);
}

void Emu_M5_Display::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
	Point pt1 = Point(x0, y0);
	Point pt2 = Point(x1, y1);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));
	line(img, pt1, pt2, _color, 1);
}

void Emu_M5_Display::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	Point pt1 = Point(x0, y0);
	Point pt2 = Point(x1, y1);
	Point pt3 = Point(x2, y2);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));

	vector<vector<Point>> contours{ {pt1, pt2, pt3} };
	drawContours(img, contours, 0, _color);
}

void Emu_M5_Display::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	Point pt1 = Point(x0, y0);
	Point pt2 = Point(x1, y1);
	Point pt3 = Point(x2, y2);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));

	vector<vector<Point>> contours{ {pt1, pt2, pt3} };
	drawContours(img, contours, 0, _color, FILLED);
}

void Emu_M5_Display::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	Point pt1 = Point(x, y);
	Point pt2 = Point(x + w, y + h);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));

	rectangle(img, pt1, pt2, _color);
}

void Emu_M5_Display::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	Point pt1 = Point(x, y);
	Point pt2 = Point(x + w, y + h);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));

	rectangle(img, pt1, pt2, _color, FILLED);
}

void Emu_M5_Display::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
	/* No implemented now! */
	cout << "\"drawRoundRect\" is NOT yet implemented!" << endl;
}

void Emu_M5_Display::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
	/* No implemented now! */
	cout << "\"fillRoundRect\" is NOT yet implemented!" << endl;
}

void Emu_M5_Display::drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
	Point center = Point(x0, y0);
	Size axes = Size(rx, ry);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));

	ellipse(img, center, axes, 0, 0, 360, _color);
}

void Emu_M5_Display::fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
	Point center = Point(x0, y0);
	Size axes = Size(rx, ry);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));

	ellipse(img, center, axes, 0, 0, 360, _color, FILLED);
}

void Emu_M5_Display::drawString(const char* str, int32_t poX, int32_t poY) {
	/* There is a slight deviation in this coordinate! */
	int base_line;
	int thickness = 1;
	int str_display_offset;
	Scalar fbg_color = transposeRGB2BGR(convert16Int2Scalar(BLACK));
	Scalar f_color = transposeRGB2BGR(convert16Int2Scalar(WHITE));

	Size size = getTextSize(str, FONT_HERSHEY_SIMPLEX, font_size, thickness, &base_line);
	str_display_offset = size.height;
	Point org = Point(poX, poY + str_display_offset);
	base_line += thickness;
	rectangle(img, org + Point(0, base_line), org + Point(size.width, -size.height), fbg_color, FILLED);
	putText(img, str, org, FONT_HERSHEY_SIMPLEX, font_size, f_color);
}

void Emu_M5_Display::setTextSize(uint8_t size) {
	textsize = size;
	switch (size) {
	case 1:
		font_size = 0.3;
		break;
	case 2:
		font_size = 0.45;
		break;
	default:
		font_size = 0.3;
		break;
	}
}

void Emu_M5_Display::setCursor(uint16_t x, uint16_t y) {
	_cursor_x = x;
	_cursor_y = y;
}

void Emu_M5_Display::print(const char* fmt) {
	printf(fmt);
}

void Emu_M5_Display::printf(const char *fmt, ...) {
	char s[256] = { '\0' };
	int len;
	va_list ap;
	va_start(ap, fmt);

	len = vsnprintf(s, 256, fmt, ap);

	va_end(ap);

	drawString(s, _cursor_x, _cursor_y);
}

void Emu_M5_Display::drawChar(int32_t x, int32_t y, uint16_t c, uint32_t color, uint32_t bg, uint32_t size) {

	bool fillbg = (bg != color);
	
	if ((size == 1) && fillbg) {
		uint8_t column[6];
		uint8_t mask = 0x1;
		for (uint8_t i = 0; i < 5; i++) {
			column[i] = font[(c * 5) + i];
		}
		column[5] = 0;

		uint8_t xp = x;
		uint8_t yp = y;
		for (uint8_t j = 0; j < 8; j++) {
			xp = x;
			for (uint8_t k = 0; k < 5; k++) {
				if (column[k] & mask) {
					drawPixel(xp, yp, color);
				}
				else {
					drawPixel(xp, yp, bg);
				}
				xp++;
			}
			mask <<= 1;
			yp++;
		}
	}
	else {
		for (int8_t i = 0; i < 6; i++) {
			uint8_t line;
			if (i == 5) {
				line = 0x0;
			}
			else {
				line = font[(c * 5) + i];
			}

			if (size == 1) { // default size
				for (int8_t j = 0; j < 8; j++) {
					if (line & 0x1) {
						drawPixel(x + i, y + j, color);
					}
					line >>= 1;
				}
			}
			else { // big size
				for (uint8_t j = 0; j < 8; j++) {
					if (line & 0x1) {
						fillRect(x + (i * size), y + (j * size), size, size, color);
					}
					else if (fillbg) {
						fillRect(x + (i * size), y + (j * size), size, size, bg);
					}
					line >>= 1;
				}
			}

		}
	}
}

int16_t Emu_M5_Display::drawChar(uint16_t uniCode, int32_t x, int32_t y, uint8_t font) {
	if (!uniCode) {
		return 0;
	}

	if (font == 1) {
#ifdef LOAD_GLCD
#ifndef LOAD_GFXFF
		// TODO: fix
		drawChar(x, y, uniCode, font_color, font_background_color, textsize);
		return 6 * textsize;
#endif
#else
#ifndef LOAD_GFXFF
		return 0;
#endif
#endif

#ifdef LOAD_GFXFF
		// Not yet implemented!
#endif
	}

	// Not yet implemented!
}

//
uint16_t Emu_M5_Display::width() {
	return LCD_WIDTH;
}

uint16_t Emu_M5_Display::height() {
	return LCD_HEIGHT;
}

uint16_t Emu_M5_Display::decodeUTF8(uint8_t* buf, uint16_t* index, uint16_t remaining) {
	uint16_t c = buf[(*index)++];
	//
#ifdef DECODE_UTF8
	// 7 bit Unicode
	if ((c & 0x80) == 0x00) return c;

	// 11 bit Unicode
	if (((c & 0xE0) == 0xC0) && (remaining > 1))
		return ((c & 0x1F) << 6) | (buf[(*index)++] & 0x3F);

	// 16 bit Unicode
	if (((c & 0xF0) == 0xE0) && (remaining > 2))
	{
		c = ((c & 0x0F) << 12) | ((buf[(*index)++] & 0x3F) << 6);
		return  c | ((buf[(*index)++] & 0x3F));
	}

	// 21 bit Unicode not supported so fall-back to extended ASCII
	// if ((c & 0xF8) == 0xF0) return c;
#endif

	return c; // fall-back to extended ASCII
}
//

int16_t Emu_M5_Display::textWidth(const char *string, uint8_t font) {
	int32_t str_width = 0;
	//uint16_t uniCode = 0;

#ifdef SMOOTH_FONT
	// Not yet implemented!
#endif

	if (font>1 && font<9) {

	}
	else {
#ifdef LOAD_GFXFF
		// Not yet implemented!
#endif
		{
#ifdef LOAD_GLCD
			while (*string++) str_width += 6;
#endif
		}
	}
	//isDigits = false
	return str_width * textsize;
}

int16_t Emu_M5_Display::drawString(const char* string, int32_t poX, int32_t poY, uint8_t font) {
	int16_t sumX = 0;
	uint8_t padding = 1, baseline = 0;
	uint16_t cwidth = textWidth(string, font);
	uint16_t cheight = 8 * textsize;

#ifdef LOAD_GFXFF
	// Not yet implemented!
#endif
#ifdef SMOOTH_FONT
	// Not yet implemented!
#endif

	if (font != 1) {
		// Not yet implemented!
	}

	if (textdatum || padX) {
		switch (textdatum) {
		case TC_DATUM:
			poX -= cwidth / 2;
			padding += 1;
			break;
		case TR_DATUM:
			poX -= cwidth;
			padding += 2;
			break;
		case ML_DATUM:
			poY -= cheight / 2;
			//padding += 0;
			break;
		case MC_DATUM:
			poX -= cwidth / 2;
			poY -= cheight / 2;
			padding += 1;
			break;
		case MR_DATUM:
			poX -= cwidth;
			poY -= cheight / 2;
			padding += 2;
			break;
		case BL_DATUM:
			poY -= cheight;
			//padding += 0;
			break;
		case BC_DATUM:
			poX -= cwidth / 2;
			poY -= cheight;
			padding += 1;
			break;
		case BR_DATUM:
			poX -= cwidth;
			poY -= cheight;
			padding += 2;
			break;
		case L_BASELINE:
			poY -= baseline;
			//padding += 0;
			break;
		case C_BASELINE:
			poX -= cwidth / 2;
			poY -= baseline;
			padding += 1;
			break;
		case R_BASELINE:
			poX -= cwidth;
			poY -= baseline;
			padding += 2;
			break;
		}
		// Check coordinates are OK, adjust if not
		if (poX < 0) poX = 0;
		if (poX + cwidth > width())   poX = width() - cwidth;
		if (poY < 0) poY = 0;
		if (poY + cheight - baseline > height()) poY = height() - cheight;
	}

	int8_t xo = 0;
#ifdef LOAD_GFXFF
	// Not yet implemented!
#endif
	uint16_t len = strlen(string);
	uint16_t n = 0;
#ifdef SMOOTH_FONT
	// Not yet implemented!
#endif
	{
		while (n < len) {
			uint16_t uniCode = decodeUTF8((uint8_t*)string, &n, len - n);
			sumX += drawChar(uniCode, poX + sumX, poY, font);
		}
	}

	// remove debug codes
	
	return sumX;
}

M5_Emulator M5;


/* Private function */
Scalar Emu_M5_Display::convert16Int2Scalar(uint16_t color){
	uint16_t b = color & 0x001F;
	uint16_t g = (color & 0x07E0) >> 5;
	uint16_t r = (color & 0xF800) >> 11;

	Scalar rgb;

	rgb[0] = (uint8_t)((r / 31.0) * 255);
	rgb[1] = (uint8_t)((g / 63.0) * 255);
	rgb[2] = (uint8_t)((b / 31.0) * 255);

	return rgb;
}

Scalar Emu_M5_Display::transposeRGB2BGR(Scalar color){
	double tmp;

	tmp = color[0];
	color[0] = color[2];
	color[2] = (uint32_t)tmp;

	return color;
}
