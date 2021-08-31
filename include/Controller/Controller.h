//
// Created by Oleksandr Degtiar on 09.01.2021.
//

#ifndef ZD50_CONTROLLER_CONTROLLER_H
#define ZD50_CONTROLLER_CONTROLLER_H

#include "Button.h"
#include "Rotary.h"
#include <Arduino.h>
#include "Menu/Menu.h"

class Controller {
public:

    typedef enum {
        VOLUME = 1,
        VOLUME_INCREMENT = 2,
        VOLUME_DECREMENT = 3,
        BUTTON_PRESS = 4,
        BUTTON_PRESSING = 5,
        ROTATE = 6,
        MUTE = 7
    } Command;

    typedef int CommandParam;

    virtual void begin(Controller *previousController, int param) {};

    virtual void end() {};

    virtual void command(Command cmd, CommandParam param) {};

    virtual void tick() {};

    virtual void onMenuClose() {};


    static Controller *getInstance();

private:
};


#endif //ZD50_CONTROLLER_CONTROLLER_H
