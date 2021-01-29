//
// Created by Oleksandr Degtiar on 05.01.2021.
//

#ifndef ZD50_BACKLIGHT_SCENE_STANDBY_H
#define ZD50_BACKLIGHT_SCENE_STANDBY_H

#include "Backlight/Scene.h"
#include "Backlight.h"

namespace BacklightScene {
    class Standby : Backlight::Scene {
    public:
        void begin();

        void frame();

        static Scene *getInstance();
    };
}

#endif //ZD50_BACKLIGHT_SCENE_STANDBY_H
