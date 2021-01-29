//
// Created by Oleksandr Degtiar on 07.01.2021.
//

#ifndef ZD50_BACKLIGHT_SCENE_SOURCE_ON_H
#define ZD50_BACKLIGHT_SCENE_SOURCE_ON_H

#include "Backlight/Scene.h"
#include "Backlight.h"

namespace BacklightScene {
    class SourcePowerOn : Backlight::Scene {
    public:
        void begin();

        static Scene *getInstance();

    private:
        void frame() override;
    };
}

#endif //ZD50_BACKLIGHT_SCENE_SOURCE_ON_H
