/*
* Global header files
* and global function/variable declarations will go here
*/
#pragma once
#ifndef DEFINES_HPP
#define DEFINES_HPP   
#include <Arduino.h>

#if (ESP32)
#define BAUD_RATE 115200
#endif

// Globally available functions
void my_delay(volatile long delay_time);

#endif //EOF DEFINES_HPP