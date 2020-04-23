# M5 LCD Emulator

## 🚧 Some ```M5.Lcd``` function NOT yet implemented! 🚧

![image](https://github.com/takkaO/M5_LCD_Emulator/blob/image/image.PNG?raw=true)

## Require
- OpenCV (Version 4.3.0 Recommended)
- VisualStudio 2019 (Windows)

## Sample code (show ```main.cpp```)
```c++
/* M5Stack CODE BEGIN */
#include "M5Stack.h"

void setup() {
	for (int i = 0; i < COLORS_NUM; i++) {
		M5.Lcd.fillScreen(COLORS[i]);
		delay(1000);
	}

	M5.Lcd.fillScreen(BLACK);
	for (int i = 1; i < 8; i++) {
		M5.Lcd.setTextSize(i);
		M5.Lcd.print("Hello World\n");
	}
}
/* M5Stack CODE END */
```

## How to use
### Windows
1. Open ```M5_LCD_Emulator.sln```.
2. Press ```Ctrl+F5```.

### Linux (Ubuntu)
1. Execute ```cd M5_LCD_Emulator/M5_LCD_Emulator```.
2. Execute  ```make```.
3. Execute ```./m5hello```.


## Setup OpenCV (Windows with VisualStudio)
1. Download OpenCV from [here](https://opencv.org/releases/).
2. Extract to install directory (exp. ```C:\```).
3. Add ```C:\opencv\build\x64\vc14\bin``` to environment path.
4. Make empty project.
5. Select ```x64``` platform.
6. Open ```Project``` -> ```Property```.
    - Open ```VC++ directory``` > ```Include directory``` and add ```C:\opencv\build\include```.
    - Open ```VC++ directory``` > ```Library directory``` and add ```C:\opencv\build\x64\vc14\lib```.
    - Open ```Linker``` > ```Input``` > ```Additional dependent files``` and add ```opencv_worldxxxd.lib```. (xxx is version, look at opencv dir)


## Setup OpenCV (Ubuntu)
0. Install some package for build OpenCV.
```
sudo apt update
sudo apt upgrade -y
sudo apt install build-essential git cmake pkg-config
sudo apt install libgtk2.0-dev libcanberra-gtk-module libcanberra-gtk3-module
```
1. Download OpenCV from [here](https://opencv.org/releases/).
2. Extract to install directory (exp. ```~/```).
3. Execute below command to build OpenCV.
```
cd ~
cd opencv-4.3.0
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j4
sudo make install
```
4. Export include path (If you need, write below command to ```~/.bashrc```).
```
export CPATH=/usr/local/include/opencv4
```

## Reference
- [【動画解説付き】OpenCV C++版をWindows10にインストールする方法【Visual Studio 2017】](https://qiita.com/shiyotsuki/items/3d30df275dee67d7c41f)
- [m5-docs/lcd.md at master · m5stack/m5-docs · GitHub](https://github.com/m5stack/m5-docs/blob/master/docs/ja/api/lcd.md)