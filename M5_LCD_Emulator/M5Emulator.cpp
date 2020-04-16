#include "M5Emulator.hpp"

Emu_M5_Display::Emu_M5_Display() {
	img = Mat::zeros(Size(LCD_WIDTH, LCD_HEIGHT), CV_8UC3);
}

void Emu_M5_Display::updateDisplay(int delay_ms) {
	imshow("M5Stack Emulator", img);
	waitKey(delay_ms);
}

void Emu_M5_Display::fillScreen(Scalar color) {
	Point pt1 = Point(0, 0);
	Point pt2 = Point(LCD_WIDTH, LCD_HEIGHT);
	rectangle(img, pt1, pt2, color, FILLED);
}

void Emu_M5_Display::drawPixel(int16_t x, int16_t y, Scalar color) {
	Point pt1 = Point(x, y);
	line(img, pt1, pt1, color, 1);
}

void Emu_M5_Display::drawFastVLine(int32_t x, int32_t y, int32_t h, Scalar color) {
	Point pt1 = Point(x, y);
	Point pt2 = Point(x, y + h);
	line(img, pt1, pt2, color, 1);
}

void Emu_M5_Display::drawFastHLine(int32_t x, int32_t y, int32_t h, Scalar color) {
	Point pt1 = Point(x, y);
	Point pt2 = Point(x + h, y);
	line(img, pt1, pt2, color, 1);
}

void Emu_M5_Display::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, Scalar color) {
	Point pt1 = Point(x0, y0);
	Point pt2 = Point(x1, y1);
	line(img, pt1, pt2, color, 1);
}

void Emu_M5_Display::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, Scalar color) {
	Point pt1 = Point(x0, y0);
	Point pt2 = Point(x1, y1);
	Point pt3 = Point(x2, y2);

	vector<vector<Point>> contours{ {pt1, pt2, pt3} };
	drawContours(img, contours, 0, color);
}

void Emu_M5_Display::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, Scalar color) {
	Point pt1 = Point(x0, y0);
	Point pt2 = Point(x1, y1);
	Point pt3 = Point(x2, y2);

	vector<vector<Point>> contours{ {pt1, pt2, pt3} };
	drawContours(img, contours, 0, color, FILLED);
}

void Emu_M5_Display::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, Scalar color) {
	Point pt1 = Point(x, y);
	Point pt2 = Point(x + w, y + h);

	rectangle(img, pt1, pt2, color);
}

void Emu_M5_Display::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Scalar color) {
	Point pt1 = Point(x, y);
	Point pt2 = Point(x + w, y + h);

	rectangle(img, pt1, pt2, color, FILLED);
}

void Emu_M5_Display::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, Scalar color) {
	/* No implemented now! */
}

void Emu_M5_Display::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, Scalar color) {
	/* No implemented now! */
}

void Emu_M5_Display::drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, Scalar color) {
	Point center = Point(x0, y0);
	Size axes = Size(rx, ry);

	ellipse(img, center, axes, 0, 0, 360, color);
}

void Emu_M5_Display::fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, Scalar color) {
	Point center = Point(x0, y0);
	Size axes = Size(rx, ry);

	ellipse(img, center, axes, 0, 0, 360, color, FILLED);
}

void Emu_M5_Display::drawString(const char* str, int32_t poX, int32_t poY) {
	/* There is a slight deviation in this coordinate! */
	int base_line;
	int thickness = 1;
	Point org = Point(poX, poY + str_display_offset);

	Size size = getTextSize(str, FONT_HERSHEY_SIMPLEX, font_size, thickness, &base_line);
	base_line += thickness;
	rectangle(img, org + Point(0, base_line - 3), org + Point(size.width, -size.height), BLACK, FILLED);
	putText(img, str, org, FONT_HERSHEY_SIMPLEX, font_size, WHITE);
}

void Emu_M5_Display::setTextSize(uint8_t size) {
	switch (size) {
	case 1:
		font_size = 0.3;
		str_display_offset = 5;
		break;
	case 2:
		font_size = 0.45;
		str_display_offset = 12;
		break;
	default:
		font_size = 0.3;
		str_display_offset = 5;
		break;
	}
}

void Emu_M5_Display::setCursor(uint16_t x, uint16_t y) {
	cursor_x = x;
	cursor_y = y;
}

void Emu_M5_Display::printf(const char* fmt, ...) {
	char s[256] = { '\0' };
	int len;
	va_list ap;
	va_start(ap, fmt);

	len = vsnprintf(s, 256, fmt, ap);

	va_end(ap);

	drawString(s, cursor_x, cursor_y);
}


M5_Emulator M5;