//
// Created by Oleksandr Degtiar on 08.01.2021.
//

#ifndef ZD50_SOURCE_POWER_ON_STATE_H
#define ZD50_SOURCE_POWER_ON_STATE_H

#include "Controller.h"

class SourcePowerOnState : Controller {
public:
    void begin(Controller *previousController);

    void end();

    void command(Controller::Command command, Controller::CommandParam param);

    static Controller *controller();
};

#endif //ZD50_SOURCE_POWER_ON_STATE_H