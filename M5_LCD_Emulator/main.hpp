#pragma once

#ifndef LINUX
#include <opencv2\opencv.hpp>
#include <windows.h>
#else
#include <opencv2/opencv.hpp>
#endif
#include <iostream>

#include "M5Emulator.hpp"
#include "M5Stack.h"

using namespace cv;
using namespace std;

void setup();
void loop();
