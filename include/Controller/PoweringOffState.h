//
// Created by Oleksandr Degtiar on 11.01.2021.
//

#ifndef ZD50_CONTROLLER_POWERINGOFFSTATE_H
#define ZD50_CONTROLLER_POWERINGOFFSTATE_H

#include "Controller.h"

class PoweringOffState : Controller {
public:
    typedef enum {
        StandBy, PowerOnSource
    } TargetState;

    void begin(Controller *previousController, int param);

    void command(Controller::Command command, Controller::CommandParam param);

    static Controller *getInstance();

    void end() override;

private:
    uint8_t targetState;

    unsigned long stopAtTime = 0;

    void tick() override;
};


#endif //ZD50_CONTROLLER_POWERINGOFFSTATE_H
