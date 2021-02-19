//
// Created by Oleksandr Degtiar on 09.01.2021.
//

#ifndef ZD50_CONTROLLER_CONTROLLER_H
#define ZD50_CONTROLLER_CONTROLLER_H

#include "Button.h"
#include "Rotary.h"
#include <Arduino.h>

class Controller {
public:

    typedef enum {
        TIMEOUT,
        VOLUME,
        VOLUME_INCREMENT,
        VOLUME_DECREMENT,
        BUTTON_PRESS,
        BUTTON_PRESSING,
        ROTATE
    } Command;

    typedef int CommandParam;

    void setTimeout(unsigned long ms) {
        timoutExpireAt = millis() + ms;
    }

    void stopTimeout() {
        timoutExpireAt = 0;
    }

    bool isTimeoutActive() {
        return timoutExpireAt != 0;
    }

    bool isTimeoutExpired() {
        return millis() > timoutExpireAt;
    }

    void reset() {
        stopTimeout();
    }

    virtual void begin(Controller *previousController) {};

    virtual void end() {};

    virtual void command(Command command, CommandParam param) {};

    static Controller *getInstance();

    void setPendingController(Controller *controller) {
        pendingController = controller;
    }

    Controller *getPendingController() const {
        return pendingController;
    }

private:
    unsigned long timoutExpireAt = 0;

    Controller *pendingController = nullptr;
};


#endif //ZD50_CONTROLLER_CONTROLLER_H
