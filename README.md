# M5 LCD Emulator

## 🚧 Some ```M5.Lcd``` function NOT yet implemented! 🚧

![image](https://github.com/takkaO/M5_LCD_Emulator/blob/image/image.PNG?raw=true)

## Require
- OpenCV (Version 4.3.0 Recommended)
- VisualStudio 2019

## Sample code
```c++
/* M5Stack CODE BEGIN */
#include "M5Stack.h"

void setup() {
	for (int i = 0; i < COLORS_NUM; i++) {
		M5.Lcd.fillScreen(COLORS[i]);
		delay(1000);
	}
	M5.Lcd.fillScreen(BLACK);
	M5.Lcd.printf("Hello World!");
	M5.Lcd.setCursor(0, 15);
	M5.Lcd.setTextSize(2);
	M5.Lcd.printf("Hello World!");
}

void loop() {
	
}
/* M5Stack CODE END */
```

## Setup OpenCV
1. Download OpenCV from [here](https://opencv.org/releases/).
2. Extract to install directory (exp. ```C:\```).
3. Add ```C:\opencv\build\x64\vc14\bin``` to environment path.
4. Make empty project.
5. Select ```x64``` platform.
6. Open ```Project``` -> ```Property```.
    - Open ```VC++ directory``` > ```Include directory``` and add ```C:\opencv\build\include```.
    - Open ```VC++ directory``` > ```Library directory``` and add ```C:\opencv\build\x64\vc14\lib```.
    - Open ```Linker``` > ```Input``` > ```Additional dependent files``` and add ```opencv_worldxxxd.lib```. (xxx is version, look at opencv dir)

## Reference
- [【動画解説付き】OpenCV C++版をWindows10にインストールする方法【Visual Studio 2017】](https://qiita.com/shiyotsuki/items/3d30df275dee67d7c41f)
- [m5-docs/lcd.md at master · m5stack/m5-docs · GitHub](https://github.com/m5stack/m5-docs/blob/master/docs/ja/api/lcd.md)