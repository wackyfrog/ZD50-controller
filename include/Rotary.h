#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include "Config.h"
//#define BUTTON_LONG_PRESS_TIME pdMS_TO_TICKS(600)
//#define ROTARY_LIMIT_RATE_MS 32

namespace Rotary {
    typedef int8_t Value;

    typedef unsigned char State;

    typedef enum {
        CW,
        CCW
    } Direction;

    void init();
}

#endif
