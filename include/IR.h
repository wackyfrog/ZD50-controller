//
// Created by Oleksandr Degtiar on 23.02.2021.
//

#ifndef ZD50_CONTROLLER_IR_H
#define ZD50_CONTROLLER_IR_H

#include "ZD50.h"

#include "Menu/Menu.h"
#include <IRLremote.h>

namespace IR {
// Delay before repeat passed through, ms
#define RC_REPEAT_DELAY 300

    typedef Nec_data_t IR_ButtonData;

    typedef enum {
        RC_POWER_BUTTON = 0,
        RC_VOLUME_UP_BUTTON,
        RC_VOLUME_DOWN_BUTTON,
        RC_MUTE_BUTTON,
        RC_PREV_BUTTON,
        RC_NEXT_BUTTON,
        RC_BUTTONS_COUNT
    } RC_ButtonId;

    typedef struct {
        RC_ButtonId button;
        IR_ButtonData ir;
    } RC_Button;

    const RC_Button ButtonsDefault[RC_BUTTONS_COUNT] = {
            {
                    RC_POWER_BUTTON,
                    0x9f00, 0x57
            },
            {
                    RC_VOLUME_UP_BUTTON,
                    0x9f00, 0x17
            },
            {
                    RC_VOLUME_DOWN_BUTTON,
                    0x9f00, 0x54
            },
            {
                    RC_MUTE_BUTTON,
                    0x9f00, 0x5b
            },
            {
                    RC_PREV_BUTTON,
                    0x9f00, 0x0a
            },
            {
                    RC_NEXT_BUTTON,
                    0x9f00, 0x43
            },
    };

    void init();

    void handleIrEvent(IR_ButtonData irButton);

    Menu::Item *getMenu();

}

//extern Menu::Item MenuIR;
#endif //ZD50_CONTROLLER_IR_H
