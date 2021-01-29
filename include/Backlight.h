//
// Created by Oleksandr Degtiar on 05.01.2021.
//

#ifndef ZD50_CONTROLLER_BACKLIGHT_H
#define ZD50_CONTROLLER_BACKLIGHT_H

#include <Arduino.h>
#include "Config.h"
#include "Backlight/Scene.h"

#define BACKLIGHT_LED_COUNT 12
#define BACKLIGHT_BUF_SIZE (3 * BACKLIGHT_LED_COUNT)

namespace Backlight {

    struct cRGB {
        uint8_t g;
        uint8_t r;
        uint8_t b;
    };

    void init();

    cRGB getPixel(uint8_t index);

    uint8_t setPixel(uint8_t index, cRGB color);

    uint8_t setSubpixel(uint16_t index, uint8_t offset, uint8_t px_value);

    void fill(cRGB color);

    void update();
}

//#include "BacklightScene/Scenes.h"

#endif //ZD50_CONTROLLER_BACKLIGHT_H

