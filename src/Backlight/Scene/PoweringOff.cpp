//
// Created by Oleksandr Degtiar on 26.01.2021.
//

#include "Backlight.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

using namespace Backlight;
using namespace BacklightScene;

static int stepsLeft = 1;
//static int bri;
//static int briStep;
static const int minBrightness = 0;
static const int maxBrightness = 4;

#define VAL_STEPS ( 10 )
#define TOTAL_STEPS ( (uint16_t)( BACKLIGHT_LED_COUNT * VAL_STEPS) )

static uint32_t frameDelay = 0;
void PoweringOff::begin() {
    stepsLeft = TOTAL_STEPS;
    frameDelay = (getFinishTime() - millis()) / TOTAL_STEPS;
}

void PoweringOff::frame() {
    if (stepsLeft == 0) {
        Backlight::update();
        done();
        return;
    }
    cRGB c;

    for (int index = 0; index < BACKLIGHT_LED_COUNT; index++) {

        uint16_t percentLeft = 100 * (uint16_t) stepsLeft / TOTAL_STEPS;
        int val = percentLeft / 2
                  + (50 * (BACKLIGHT_LED_COUNT - (uint16_t)index)) /  BACKLIGHT_LED_COUNT;

        HSV8_TO_CRGB(HSV_HUE_DEGREE(30), 100 - percentLeft, HSV_VAL_PERCENT(val > 100 ? 100 : val), &c);

        Backlight::setPixel(LED_INDEX(index), c);
    }
    Backlight::update();
    stepsLeft--;
    nextFrameDelay(frameDelay);
}

Scene *PoweringOff::getInstance() {
    static PoweringOff inst;
    return (Scene *) &inst;
}
