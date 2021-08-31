//
// Created by Oleksandr Degtiar on 21.10.2020.
//

#ifndef ZD50_H
#define ZD50_H

#include "Config.h"

#if ZD50_DEBUG_SERIAL
#include "SerialOut.h"
#endif

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
#include "IR.h"

#define VOLUME_MAX_VALUE (MAX_ATTENUATION_LEVEL + 1)
#define VOLUME_MIN_VALUE 0
#define VOLUME_START_VALUE 20

#define CONTROLLER_TICK_MS 10

namespace ZD50 {
    void init();

    void command(Controller::Command command, Controller::CommandParam param = 0);

    void setVolume(int newVolume);

    int getVolume();

    Controller *getController();

    void setController(Controller *newController, int param = 0);


    namespace Attenuator = Attenuator;

    namespace Backlight = Backlight;

    namespace Display = Display;

    namespace Luminance = Luminance;

#if ZD50_DEBUG_SERIAL
    extern TinySerialOut SerialOut;
#endif
};

#endif //ZD50_H
