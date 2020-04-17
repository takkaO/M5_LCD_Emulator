#include "M5Emulator.hpp"

Emu_M5_Display::Emu_M5_Display() {
	img = Mat::zeros(Size(LCD_WIDTH, LCD_HEIGHT), CV_8UC3);
}

void Emu_M5_Display::updateDisplay(int delay_ms) {
	imshow("M5Stack Emulator", img);
	waitKey(delay_ms);
}

void Emu_M5_Display::fillScreen(uint16_t color) {
	Point pt1 = Point(0, 0);
	Point pt2 = Point(LCD_WIDTH, LCD_HEIGHT);
	Scalar _color = transposeRGB2BGR(convert16Int2Scalar(color));
	rectangle(img, pt1, pt2, _color, FILLED);
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
}

void Emu_M5_Display::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
	/* No implemented now! */
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
	Point org = Point(poX, poY + str_display_offset);
	Scalar black = transposeRGB2BGR(convert16Int2Scalar(BLACK));
	Scalar white = transposeRGB2BGR(convert16Int2Scalar(WHITE));

	Size size = getTextSize(str, FONT_HERSHEY_SIMPLEX, font_size, thickness, &base_line);
	base_line += thickness;
	rectangle(img, org + Point(0, base_line - 3), org + Point(size.width, -size.height), black, FILLED);
	putText(img, str, org, FONT_HERSHEY_SIMPLEX, font_size, white);
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

	drawString(s, cursor_x, cursor_y);
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
