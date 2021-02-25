//
// Created by Oleksandr Degtiar on 21.01.2021.
//

#ifndef ZD50_CONFIG_H
#define ZD50_CONFIG_H
#include <Arduino.h>

#ifdef ARDUINO_AVR_UNO
#include "Config/uno.h"
#endif

#ifdef __AVR_ATmega324PA__
    #include "Config/atmega324pa.h"
#endif

#ifdef __AVR_ATmega32U4__
    #include "Config/atmega32u4.h"
#endif

#endif //ZD50_CONFIG_H
