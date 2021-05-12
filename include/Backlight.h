//
// Created by Oleksandr Degtiar on 05.01.2021.
//

#ifndef ZD50_CONTROLLER_BACKLIGHT_H
#define ZD50_CONTROLLER_BACKLIGHT_H

#include <Arduino.h>
#include "Config.h"
#include "Backlight/Scene.h"
#include "FastHSV2RGB/fast_hsv2rgb.h"

#define BACKLIGHT_LED_COUNT 12
#define BACKLIGHT_BUF_SIZE (3 * BACKLIGHT_LED_COUNT)

#define HSV_HUE_DEGREE(x) ( x > 359 ? HSV_HUE_MAX : (((uint32_t)x * (uint32_t)HSV_HUE_MAX) / 360) )
#define HSV_VAL_PERCENT(x) ( (uint8_t) ( (uint16_t)x * (uint16_t)BACKLIGHT_MAX_LIGHTNESS / 100) )
#define HSV_SAT_PERCENT(x) ( (uint8_t) ( (uint16_t)x * (uint16_t)HSV_SAT_MAX / 100 ) )

#define LED_INDEX(i) (i < 10 ? i + 2 : i - 10)
#define HSV8_TO_CRGB(hue, sat, val, crgb) \
    (fast_hsv2rgb_8bit(                   \
    HSV_HUE_DEGREE(hue), HSV_SAT_PERCENT(sat), HSV_VAL_PERCENT(val), \
    crgb.r, crgb.g, crgb.b))


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

