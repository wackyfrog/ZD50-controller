//
// Created by Oleksandr Degtiar on 25.01.2021.
//

#ifndef ZD50_CONTROLLER_BUTTON_H
#define ZD50_CONTROLLER_BUTTON_H

#include "stdint.h"

namespace Button {
#define VIRTUAL_PRESS_TIMEOUT ( 250 )

    typedef enum {
        UNPRESSED = 0,
        SHORT_PRESS = 1,
        MIDDLE_PRESS = 2,
        LONG_PRESS = 3,
        __LENGTH__
    } State;


    typedef struct {
        unsigned long time;
        State nextState;
    } StateTransition;

    const StateTransition statesTransition[__LENGTH__] = {
            {30,  SHORT_PRESS}, // UNPRESSED -> PRESS
            {800, MIDDLE_PRESS}, // PRESS -> MIDDLE_PRESS
            {800, LONG_PRESS}, // MIDDLE_PRESS -> LONG_PRESS
            {800, LONG_PRESS} // LONG_PRESS
    };

    void init();

    unsigned long getPressingTime();

    State getState();

    void virtualPress();

    void virtualUnpress();
}


#endif //ZD50_CONTROLLER_BUTTON_H
