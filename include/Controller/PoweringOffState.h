//
// Created by Oleksandr Degtiar on 11.01.2021.
//

#ifndef ZD50_CONTROLLER_POWERINGOFFSTATE_H
#define ZD50_CONTROLLER_POWERINGOFFSTATE_H

#include "Controller.h"

class PoweringOffState : Controller {
public:
    void begin(Controller *previousController);

    void command(Controller::Command command, Controller::CommandParam param);

    static Controller *getInstance();

    void end() override;
};


#endif //ZD50_CONTROLLER_POWERINGOFFSTATE_H
