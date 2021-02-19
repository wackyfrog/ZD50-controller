//
// Created by Oleksandr Degtiar on 25.01.2021.
//

#ifndef ZD50_CONTROLLER_BUTTON_H
#define ZD50_CONTROLLER_BUTTON_H

#include "stdint.h"

namespace Button {

    typedef enum {
        UNPRESSED,
        SHORT_PRESS,
        MIDDLE_PRESS,
        LONG_PRESS,
        __LENGTH__
    } State;


    typedef struct {
        unsigned long time;
        State nextState;
    } StateTransition;

    const StateTransition statesTransition[__LENGTH__] = {
            {100,  SHORT_PRESS}, // UNPRESSED -> PRESS
            {1000, MIDDLE_PRESS}, // PRESS -> MIDDLE_PRESS
            {1000, LONG_PRESS}, // MIDDLE_PRESS -> LONG_PRESS
            {1000, LONG_PRESS} // LONG_PRESS
    };

    void init();

    unsigned long getPressingTime();

    State getState();
}


#endif //ZD50_CONTROLLER_BUTTON_H
