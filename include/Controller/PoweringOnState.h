//
// Created by Oleksandr Degtiar on 11.01.2021.
//

#ifndef ZD50_CONTROLLER_POWERINGONSTATE_H
#define ZD50_CONTROLLER_POWERINGONSTATE_H

#include "Controller.h"

class PoweringOnState : Controller {
public:
    void begin(Controller *previousController, int param);

    static Controller *getInstance();

    void end() override;

private:
    void tick() override;

    unsigned long stopAtTime;
};


#endif //ZD50_CONTROLLER_POWERINGONSTATE_H
