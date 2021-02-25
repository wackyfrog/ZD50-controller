//
// Created by Oleksandr Degtiar on 21.10.2020.
//

#ifndef ZD50_H
#define ZD50_H

#include "Config.h"
#include <Arduino.h>
#include <AceRoutine.h>

#include "PowerControl.h"
#include "Backlight.h"
#include "Attenuator.h"
#include "Display.h"
#include "Luminance.h"
#include "Rotary.h"
#include "Button.h"
#include "Controller/Controller.h"
#include "Settings.h"

#define VOLUME_MAX_VALUE (MAX_ATTENUATION_LEVEL + 1)
#define VOLUME_MIN_VALUE 0
#define VOLUME_START_VALUE 0

namespace ZD50 {
    void init();

    void command(Controller::Command command, Controller::CommandParam param);

    void setVolume(int newVolume);

    int getVolume();

    Controller *getController();

    void setController(Controller *newController, int param = 0);


    namespace Attenuator = Attenuator;

    namespace Backlight = Backlight;

    namespace Display = Display;

    namespace Luminance = Luminance;

    extern SERIAL_OUT_T &SerialOut;
};

#endif //ZD50_H
