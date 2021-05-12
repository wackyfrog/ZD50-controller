//
// Created by Oleksandr Degtiar on 26.01.2021.
//

#include "Backlight.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"
#include "Controller/States.h"

using namespace Backlight;
using namespace BacklightScene;

#define HUE_START 230
#define HUE_FINISH 30
#define HUE_STEPS (abs(HUE_FINISH - HUE_START) )
#define TOTAL_STEPS (uint32_t) HUE_STEPS

static cRGB c;

static uint32_t frameDelay = 0;

static int hue = HUE_START;

static int stepsLeft = 0;

void PoweringOn::begin() {
    hue = HUE_START;
    frameDelay = (getFinishTime() - millis()) / TOTAL_STEPS;
    stepsLeft = TOTAL_STEPS;
}

void PoweringOn::frame() {
    HSV8_TO_CRGB(hue, stepsLeft < 25 ? stepsLeft << 2 : 100, 100, &c);
    Backlight::fill(c);
    Backlight::update();
    hue--;
    if (hue < 0) {
        hue = 359;
    }
    if (stepsLeft == 0) {
        done();
    } else {
        stepsLeft--;
        nextFrameDelay(frameDelay);
    }
}

Scene *PoweringOn::getInstance() {
    static PoweringOn inst;
    return (Scene *) &inst;
}

