#pragma once

/* This file is dummy for M5Stack programs */

#ifndef LINUX
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep(1000*(x))
#endif

#include "M5Emulator.hpp"

void delay(unsigned int ms);
