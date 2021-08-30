//
// Created by Oleksandr Degtiar on 23.02.2021.
//

#ifndef ZD50_CONTROLLER_IR_H
#define ZD50_CONTROLLER_IR_H

#include "ZD50.h"
#include "Menu/Menu.h"
#include <IRLremote.h>

namespace IR {
    typedef Nec_data_t IR_ButtonData;

    typedef enum {
        RC_POWER_BUTTON = 0,
        RC_VOLUME_UP_BUTTON,
        RC_VOLUME_DOWN_BUTTON,
        RC_MUTE_BUTTON,
        RC_BUTTONS_COUNT
    } RC_ButtonId;

    typedef struct {
        RC_ButtonId button;
        IR_ButtonData ir;
    } RC_Button;

//    typedef RC_Button *RC_Buttons;

    void init();

    void handleIrEvent(IR_ButtonData ir_button);

    Menu::Item *getMenu();

}
//extern Menu::Item MenuIR;
#endif //ZD50_CONTROLLER_IR_H
