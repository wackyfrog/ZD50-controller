//
// Created by Oleksandr Degtiar on 05.01.2021.
//

#include "Backlight.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

using namespace Backlight;
using namespace BacklightScene;


static uint8_t state = 0;
static int bri;
static int briStep;
const int minBrightness = 0;
const int maxBrightness = 45;

static uint16_t hue;
static uint8_t val;
static cRGB color;

void Standby::begin() {
    state = 0;
    hue = HSV_HUE_MIN;
}

void Standby::frame() {
    switch (state) {
        case 0:
            bri = 0;
            briStep = 1;
            state++;
            break;

        case 1:
            state++;
            Backlight::fill((Backlight::cRGB) {0, 0, 0});
            Backlight::update();

            nextFrameDelay(1000);
            break;

        case 2:
            fast_hsv2rgb_32bit(0, 10, bri, &color.r, &color.g, &color.b);
            fill(color);
            Backlight::update();

            bri += briStep;
            if (bri > maxBrightness) {
                bri = maxBrightness;
                briStep = -1;
                nextFrameDelay(1000);
//                hue += 20;
//                if (hue > HSV_HUE_MAX) {
//                    hue = HSV_HUE_MIN;
//                }

            } else if (bri < minBrightness) {
                bri = minBrightness;
                briStep = 1;
                nextFrameDelay(1000);
//                hue += 20;
//                if (hue > HSV_HUE_MAX) {
//                    hue = HSV_HUE_MIN;
//                }

            } else {
                nextFrameDelay(30);
            }
            break;
    }
}

Scene *Standby::getInstance() {
    static Standby inst;
    return (Scene *) &inst;
}

