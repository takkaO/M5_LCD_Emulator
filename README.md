# M5 LCD Emulator

### 🚧 Some ```M5.Lcd``` function NOT yet implemented! 🚧

## Environment
1. Download OpenCV from [here](https://opencv.org/releases/).
2. Extract to install directory (exp. ```C:\```).
3. Add ```C:\opencv\build\x64\vc14\bin``` to environment path.
4. Make empty project.
5. Select ```x64``` platform.
6. Open ```Project``` -> ```Property```.
    - Open ```VC++ directory``` > ```Include directory``` and add ```C:\opencv\build\include```.
    - Open ```VC++ directory``` > ```Library directory``` and add ```C:\opencv\build\x64\vc14\lib```.
    - Open ```Linker``` > ```Input``` > ```Additional dependent files``` and add ```opencv_worldxxxd.lib```. (xxx is version, look at opencv dir)