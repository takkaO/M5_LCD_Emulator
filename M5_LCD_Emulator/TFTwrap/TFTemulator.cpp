
#include "TFTemulator.hpp"

using namespace std;
using namespace  cv;

TFT_Emulator::TFT_Emulator() {

}

TFT_Emulator::TFT_Emulator(uint32_t width, uint32_t height) {
	_width = width;
	_height = height;

	// Make canvas
	img = Mat::zeros(Size(_width, _height), CV_8UC3);
}

/* ----------------------------- */
/*      background function      */
/* ----------------------------- */

uint16_t TFT_Emulator::width() {
	return _width;
}

uint16_t TFT_Emulator::height() {
	return _height;
}

uint16_t TFT_Emulator::decodeUTF8(uint8_t* buf, uint16_t* index, uint16_t remaining) {
	uint16_t c = buf[(*index)++];

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

int16_t TFT_Emulator::textWidth(const char *str) {
	return textWidth(str, textfont);
}

int16_t TFT_Emulator::textWidth(const char *str, uint8_t font) {
	int32_t str_width = 0;
	//uint16_t uniCode = 0;

#ifdef SMOOTH_FONT
	// Not yet implemented!
#endif

	if (font > 1 && font < 9) {

	}
	else {
#ifdef LOAD_GFXFF
		// Not yet implemented!
#endif
		{
#ifdef LOAD_GLCD
			while (*str++) str_width += 6;
#endif
		}
	}
	//isDigits = false
	return str_width * textsize;
}

int16_t TFT_Emulator::fontHeight() {
	return 8 * textsize;
}

uint16_t TFT_Emulator::color565(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

uint32_t TFT_Emulator::color16to24(uint16_t color565) {
	uint8_t r = (color565 >> 8) & 0xF8; r |= (r >> 5);
	uint8_t g = (color565 >> 3) & 0xFC; g |= (g >> 6);
	uint8_t b = (color565 << 3) & 0xF8; b |= (b >> 5);

	return ((uint32_t)r << 16) | ((uint32_t)g << 8) | ((uint32_t)b << 0);
}

void TFT_Emulator::setTextColor(uint16_t color, uint16_t backgroundcolor) {
	textcolor = color;
	textbgcolor = backgroundcolor;
}

void TFT_Emulator::setTextSize(uint8_t size) {
	if (size < 1 || 7 < size) {
		cout << "[Warning] Text size must be 0 < textsize < 8" << endl;
		return;
	}
	textsize = size;
}

void TFT_Emulator::setCursor(uint16_t x, uint16_t y) {
	cursor_x = x;
	cursor_y = y;
}


/* ----------------------------- */
/*       drawing function        */
/* ----------------------------- */
void TFT_Emulator::fillScreen(uint16_t color) {
	Point pt1 = Point(0, 0);
	Point pt2 = Point(_width, _height);
	Scalar _color = transposeRGB2BGR(color);
	rectangle(img, pt1, pt2, _color, FILLED);
}

void TFT_Emulator::drawPixel(int16_t x, int16_t y, uint16_t color) {
	Point pt1 = Point(x, y);
	Scalar _color = transposeRGB2BGR(color);
	line(img, pt1, pt1, _color, 1);
}

void TFT_Emulator::drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color) {
	if (h <= 0) {
		return;
	}
	Point pt1 = Point(x, y);
	Point pt2 = Point(x, y + h - 1);
	Scalar _color = transposeRGB2BGR(color);
	line(img, pt1, pt2, _color, 1);
}

void TFT_Emulator::drawFastHLine(int32_t x, int32_t y, int32_t h, uint32_t color) {
	if (h <= 0) {
		return;
	}
	Point pt1 = Point(x, y);
	Point pt2 = Point(x + h - 1, y);
	Scalar _color = transposeRGB2BGR(color);
	line(img, pt1, pt2, _color, 1);
}

void TFT_Emulator::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
	Point pt1 = Point(x0, y0);
	Point pt2 = Point(x1, y1);
	Scalar _color = transposeRGB2BGR(color);
	line(img, pt1, pt2, _color, 1);
}

void TFT_Emulator::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	Point pt1 = Point(x0, y0);
	Point pt2 = Point(x1, y1);
	Point pt3 = Point(x2, y2);
	Scalar _color = transposeRGB2BGR(color);

	vector<vector<Point>> contours{ {pt1, pt2, pt3} };
	drawContours(img, contours, 0, _color);
}

void TFT_Emulator::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	Point pt1 = Point(x0, y0);
	Point pt2 = Point(x1, y1);
	Point pt3 = Point(x2, y2);
	Scalar _color = transposeRGB2BGR(color);

	vector<vector<Point>> contours{ {pt1, pt2, pt3} };
	drawContours(img, contours, 0, _color, FILLED);
}

void TFT_Emulator::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	if (w == 0 || h == 0) {
		return;
	}
	Point pt1 = Point(x, y);
	Point pt2 = Point(x + w - 1, y + h - 1);
	Scalar _color = transposeRGB2BGR(color);

	rectangle(img, pt1, pt2, _color);
}

void TFT_Emulator::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	if (w == 0 || h == 0) {
		return;
	}
	Point pt1 = Point(x, y);
	Point pt2 = Point(x + w - 1, y + h - 1);
	Scalar _color = transposeRGB2BGR(color);

	rectangle(img, pt1, pt2, _color, FILLED);
}

void TFT_Emulator::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
	// smarter version
	drawFastHLine(x + r, y, w - r - r, color); // Top
	drawFastHLine(x + r, y + h - 1, w - r - r, color); // Bottom
	drawFastVLine(x, y + r, h - r - r, color); // Left
	drawFastVLine(x + w - 1, y + r, h - r - r, color); // Right
	// draw four corners
	drawCircleHelper(x + r, y + r, r, 1, color);
	drawCircleHelper(x + w - r - 1, y + r, r, 2, color);
	drawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
	drawCircleHelper(x + r, y + h - r - 1, r, 8, color);
}

void TFT_Emulator::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
	// smarter version
	fillRect(x, y + r, w, h - r - r, color);

	// draw four corners
	fillCircleHelper(x + r, y + h - r - 1, r, 1, w - r - r - 1, color);
	fillCircleHelper(x + r, y + r, r, 2, w - r - r - 1, color);
}

void TFT_Emulator::drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
	Point center = Point(x0, y0);
	Size axes = Size(rx, ry);
	Scalar _color = transposeRGB2BGR(color);

	ellipse(img, center, axes, 0, 0, 360, _color);
}

void TFT_Emulator::fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
	Point center = Point(x0, y0);
	Size axes = Size(rx, ry);
	Scalar _color = transposeRGB2BGR(color);

	ellipse(img, center, axes, 0, 0, 360, _color, FILLED);
}

void TFT_Emulator::drawCircleHelper(int32_t x0, int32_t y0, int32_t r, uint8_t cornername, uint32_t color)
{
	int32_t f = 1 - r;
	int32_t ddF_x = 1;
	int32_t ddF_y = -2 * r;
	int32_t x = 0;

	while (x < r) {
		if (f >= 0) {
			r--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		if (cornername & 0x4) {
			drawPixel(x0 + x, y0 + r, color);
			drawPixel(x0 + r, y0 + x, color);
		}
		if (cornername & 0x2) {
			drawPixel(x0 + x, y0 - r, color);
			drawPixel(x0 + r, y0 - x, color);
		}
		if (cornername & 0x8) {
			drawPixel(x0 - r, y0 + x, color);
			drawPixel(x0 - x, y0 + r, color);
		}
		if (cornername & 0x1) {
			drawPixel(x0 - r, y0 - x, color);
			drawPixel(x0 - x, y0 - r, color);
		}
	}
}

void TFT_Emulator::fillCircleHelper(int32_t x0, int32_t y0, int32_t r, uint8_t cornername, int32_t delta, uint32_t color)
{
	int32_t f = 1 - r;
	int32_t ddF_x = 1;
	int32_t ddF_y = -r - r;
	int32_t y = 0;

	delta++;
	while (y < r) {
		if (f >= 0) {
			r--;
			ddF_y += 2;
			f += ddF_y;
		}
		y++;
		//x++;
		ddF_x += 2;
		f += ddF_x;

		if (cornername & 0x1)
		{
			drawFastHLine(x0 - r, y0 + y, r + r + delta, color);
			drawFastHLine(x0 - y, y0 + r, y + y + delta, color);
		}
		if (cornername & 0x2) {
			drawFastHLine(x0 - r, y0 - y, r + r + delta, color); // 11995, 1090
			drawFastHLine(x0 - y, y0 - r, y + y + delta, color);
		}
	}
}

/* --------------------------------- */
/*      draw character function      */
/* --------------------------------- */

void TFT_Emulator::drawChar(int32_t x, int32_t y, uint16_t c, uint32_t color, uint32_t bg, uint32_t size) {
	//cout << int(c) << endl;
	bool fillbg = (bg != color);

	if ((size == 1) && fillbg) {
		uint8_t column[6];
		uint8_t mask = 0x1;
		for (uint8_t i = 0; i < 5; i++) {
			column[i] = font[(c * 5) + i];
		}
		column[5] = 0;

		uint32_t xp = x;
		uint32_t yp = y;
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

int16_t TFT_Emulator::drawChar(uint16_t uniCode, int32_t x, int32_t y) {
	return drawChar(uniCode, x, y, textfont);
}

int16_t TFT_Emulator::drawChar(uint16_t uniCode, int32_t x, int32_t y, uint8_t font) {
	if (!uniCode) {
		return 0;
	}

	if (font == 1) {
#ifdef LOAD_GLCD
#ifndef LOAD_GFXFF
		// TODO: fix
		drawChar(x, y, uniCode, textcolor, textbgcolor, textsize);
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
	return 0;
}


int16_t TFT_Emulator::drawString(const string& str, int32_t poX, int32_t poY, uint8_t font) {
	return drawString(str.c_str(), poX, poY, font);

}

int16_t TFT_Emulator::drawString(const string& str, int32_t poX, int32_t poY) {
	return drawString(str.c_str(), poX, poY, textfont);
}

int16_t TFT_Emulator::drawString(const char* str, int32_t poX, int32_t poY) {
	return drawString(str, poX, poY, textfont);
}

int16_t TFT_Emulator::drawString(const char* str, int32_t poX, int32_t poY, uint8_t font) {
	int16_t sumX = 0;
	uint8_t padding = 1, baseline = 0;
	uint16_t cwidth = textWidth(str, font);
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
	uint16_t len = strlen(str);
	uint16_t n = 0;
#ifdef SMOOTH_FONT
	// Not yet implemented!
#endif
	{
		while (n < len) {
			uint16_t uniCode = decodeUTF8((uint8_t*)str, &n, len - n);
			sumX += drawChar(uniCode, poX + sumX, poY, font);
		}
	}

	// remove debug codes

	return sumX;
}


void TFT_Emulator::printf(const char *fmt, ...) {
	char s[1024] = { '\0' };
	int len;
	bool LF_flag = false;
	va_list ap;
	uint16_t cheight = 8 * textsize;

	va_start(ap, fmt);
	len = vsnprintf(s, 1024, fmt, ap);
	va_end(ap);


	if (s[0] == '\n') {
		cursor_y += cheight;
	}
	if (len > 0 && s[len - 1] == '\n') {
		LF_flag = true;
	}

	char *token, *next_token;
#ifdef _MSC_VER
	token = strtok_s(s, "\n", &next_token);
#else
	token = strtok_r(s, "\n", &next_token);
#endif
	while (token != NULL) {
		drawString(token, cursor_x, cursor_y);
#ifdef _MSC_VER
		token = strtok_s(NULL, "\n", &next_token);
#else
		token = strtok_r(NULL, "\n", &next_token);
#endif
		if (token != NULL) {
			cursor_y += cheight;
		}
	}

	if (LF_flag) {
		cursor_y += cheight;
	}
}

void TFT_Emulator::print(const char *fmt) {
	printf(fmt);
}

/* ----------------------------- */
/*       private function        */
/* ----------------------------- */
Scalar TFT_Emulator::convert16Int2Scalar(uint16_t color) {
	uint32_t _color = color16to24(color);

	Scalar rgb;

	rgb[0] = (uint8_t)((_color & 0xFF0000) >> 16);
	rgb[1] = (uint8_t)((_color & 0x00FF00) >> 8);
	rgb[2] = (uint8_t)((_color & 0x0000FF) >> 0);

	return rgb;
}

Scalar TFT_Emulator::transposeRGB2BGR(uint16_t color) {
	return transposeRGB2BGR(convert16Int2Scalar(color));
}

Scalar TFT_Emulator::transposeRGB2BGR(Scalar color) {
	double tmp;

	tmp = color[0];
	color[0] = color[2];
	color[2] = (uint32_t)tmp;

	return color;
}
