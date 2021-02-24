//
// Created by Oleksandr Degtiar on 05.01.2021.
//

#ifndef ZD50_BACKLIGHT_SCENE_STANDBY_H
#define ZD50_BACKLIGHT_SCENE_STANDBY_H

#include "Backlight/Scene.h"
#include "Backlight.h"

namespace BacklightScene {
    class Standby : Backlight::Scene {
        char stepLightness = 1;
        uint16_t hue = HSV_HUE_MIN;
        uint8_t lightnessMin = HSV_VAL_MIN;
        uint8_t lightnessMax = 45;
        uint8_t saturation = 20;

    public:
        void begin();

        void frame();

        static Scene *getInstance();


        int getHue() const;

        int setHue(int newValue);

        int getSaturation() const;

        int setSaturation(int newValue);

        int getLightnessMin() const;

        int setLightnessMin(int newValue);

        int getLightnessMax() const;

        int setLightnessMax(int newValue);

        void preview();
    };
}

#endif //ZD50_BACKLIGHT_SCENE_STANDBY_H
