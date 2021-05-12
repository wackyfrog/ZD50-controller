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

//static uint8_t val;
static cRGB color;

void Standby::begin() {
    state = 0;
}

void Standby::frame() {
    switch (state) {
        case 0:
            bri = 0;
            stepLightness = 1;
            state++;
            break;

        case 1:
            state++;
            Backlight::fill((Backlight::cRGB) {0, 0, 0});
            Backlight::update();

            nextFrameDelay(1000);
            break;

        case 2:
            fast_hsv2rgb_8bit(hue, saturation, bri, &color.r, &color.g, &color.b);
            fill(color);
            Backlight::update();

            bri += stepLightness;
            if (bri > lightnessMax) {
                bri = lightnessMax;
                stepLightness = -1;
                nextFrameDelay(1000);

            } else if (bri < lightnessMin) {
                bri = lightnessMin;
                stepLightness = 1;
                nextFrameDelay(1000);

            } else {
                nextFrameDelay(30);
            }
            break;

    }
}

void Standby::preview() {
    fast_hsv2rgb_8bit(hue, saturation, lightnessMax, &color.r, &color.g, &color.b);
    fill(color);
    update();
}

Scene *Standby::getInstance() {
    static Standby inst;
    return (Scene *) &inst;
}

int Standby::getHue() const {
    return hue;
}

int Standby::setHue(int newValue) {
    if (newValue > HSV_HUE_MAX) {
        newValue = HSV_HUE_MIN;
    } else if (newValue < HSV_HUE_MIN) {
        newValue = HSV_HUE_MAX;
    }
    return hue = newValue;
}

int Standby::getSaturation() const {
    return saturation;
}

int Standby::setSaturation(int newValue) {
    if (newValue > HSV_SAT_MAX) {
        newValue = HSV_SAT_MAX;
    } else if (newValue < HSV_SAT_MIN) {
        newValue = HSV_SAT_MIN;
    }
    return saturation = newValue;
}

int Standby::getLightnessMin() const {
    return lightnessMin;
}

int Standby::setLightnessMin(int newValue) {
    if (newValue > lightnessMax) {
        newValue = lightnessMax;
    } else if (newValue < HSV_SAT_MIN) {
        newValue = HSV_SAT_MIN;
    }
    return lightnessMin = newValue;
}

int Standby::getLightnessMax() const {
    return lightnessMax;
}

int Standby::setLightnessMax(int newValue) {
    if (newValue > BACKLIGHT_MAX_LIGHTNESS) {
        newValue = BACKLIGHT_MAX_LIGHTNESS;
    } else if (newValue < lightnessMin) {
        newValue = lightnessMin;
    }
    return lightnessMax = newValue;
}

