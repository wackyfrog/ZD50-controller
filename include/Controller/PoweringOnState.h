//
// Created by Oleksandr Degtiar on 11.01.2021.
//

#ifndef ZD50_CONTROLLER_POWERINGONSTATE_H
#define ZD50_CONTROLLER_POWERINGONSTATE_H

#include "Controller.h"

class PoweringOnState : Controller {
public:
    void begin(Controller *previousController);

    void command(Controller::Command command, Controller::CommandParam param);

    static Controller *controller();

    void end() override;
};


#endif //ZD50_CONTROLLER_POWERINGONSTATE_H
