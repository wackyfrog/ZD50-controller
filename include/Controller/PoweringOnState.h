//
// Created by Oleksandr Degtiar on 11.01.2021.
//

#ifndef ZD50_CONTROLLER_POWERINGONSTATE_H
#define ZD50_CONTROLLER_POWERINGONSTATE_H

#define FAST_SOFT_START_DURATION ( (uint32_t)4000 )
#define SOFT_START_DURATION ( (uint32_t)10000 )

#include "Controller.h"

class PoweringOnState : Controller {
public:
    void begin(Controller *previousController, int param);

    static Controller *getInstance();

    void end() override;

private:
    void tick() override;

    void frame() const;
};


#endif //ZD50_CONTROLLER_POWERINGONSTATE_H
