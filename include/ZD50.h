//
// Created by Oleksandr Degtiar on 21.10.2020.
//

#ifndef ZD50_H
#define ZD50_H

#include "Config.h"
#include <Arduino.h>
#include <AceRoutine.h>
#include "SerialOut.h"
#include "PowerControl.h"
#include "Backlight.h"
#include "Attenuator.h"
#include "Display.h"
#include "Luminance.h"
#include "Rotary.h"
#include "Button.h"
#include "Controller/Controller.h"

#define VOLUME_MAX_VALUE (MAX_ATTENUATION_LEVEL + 1)
#define VOLUME_MIN_VALUE 0
#define VOLUME_START_VALUE 0

namespace ZD50 {
    void init();

    Controller *getController();

    void setVolume(int newVolume);

    int getVolume();

    void setController(Controller *newController, Controller *nextController = nullptr);

    namespace Attenuator = Attenuator;

    namespace Backlight = Backlight;

    namespace Display = Display;

    namespace Luminance = Luminance;

#ifdef ZD50_DEBUG_SERIAL
    extern TinySerialOut Serial;
#endif
};

#endif //ZD50_H
