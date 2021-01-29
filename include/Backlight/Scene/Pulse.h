//
// Created by Oleksandr Degtiar on 26.01.2021.
//

#ifndef ZD50_CONTROLLER_PULSE_H
#define ZD50_CONTROLLER_PULSE_H

#include "Backlight/Scene.h"
#include "Backlight.h"

namespace BacklightScene {
    class Pulse : Backlight::Scene {
    public:
        void begin();

        void frame();

        static Scene *getInstance();
    };
}


#endif //ZD50_CONTROLLER_PULSE_H
