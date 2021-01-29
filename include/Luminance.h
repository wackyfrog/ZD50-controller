//
// Created by Oleksandr Degtiar on 21.10.2020.
//

#ifndef ZD50_LUMINANCE_H
#define ZD50_LUMINANCE_H

#include "Config.h"

#ifdef __AVR_ATmega324PA__
#define LUMINANCE_PIN _BV(3)
#define LUMINANCE_INIT() DDRA |= LUMINANCE_PIN
#endif

namespace Luminance {
    void init();

    int update();

    int getValue();
};

#endif //ZD50_LUMINANCE_H
