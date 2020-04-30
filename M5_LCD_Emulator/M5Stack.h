#pragma once

/* This file is dummy for M5Stack programs */

#ifndef LINUX
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep(1000*(x))
#endif

#include "M5Emulator.hpp"

#ifndef BUTTON_A
#define BUTTON_A 0
#endif // !BUTTON_A
#ifndef BUTTON_B
#define BUTTON_B 1
#endif // !BUTTON_B
#ifndef BUTTON_C
#define BUTTON_C 2
#endif // !BUTTON_C

void delay(unsigned int ms);
