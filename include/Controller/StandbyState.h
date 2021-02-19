//
// Created by Oleksandr Degtiar on 22.10.2020.
//

#ifndef ZD_50_CONTROLLER_DISPATCHER_STATESTANDBY_H
#define ZD_50_CONTROLLER_DISPATCHER_STATESTANDBY_H

#include "Controller.h"

class StandbyState : Controller {
public:
    void begin(Controller *previousController);

    void command(Controller::Command command, Controller::CommandParam param);

    static Controller *getInstance();

    void end() override;
};

#endif //ZD_50_CONTROLLER_DISPATCHER_STATESTANDBY_H
