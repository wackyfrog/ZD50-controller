//
// Created by Oleksandr Degtiar on 08.01.2021.
//

#ifndef ZD50_CONTROLLER_DISPATCHER_ONSTATE_H
#define ZD50_CONTROLLER_DISPATCHER_ONSTATE_H

#include "Controller.h"

class PowerOnState : Controller {
public:
    void begin(Controller *previousController);

    void command(Controller::Command command, Controller::CommandParam param);

    static Controller *controller();

    void end() override;
};

#endif //ZD50_CONTROLLER_DISPATCHER_ONSTATE_H
