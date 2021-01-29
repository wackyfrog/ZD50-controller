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
const int maxBrightness = 4;

void Standby::begin() {
    ZD50::Serial.println(F("[StandbyScene::begin]"));
    state = 0;
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
            fill((Backlight::cRGB) {(uint8_t) bri, (uint8_t) bri, (uint8_t) bri});
            Backlight::update();

            bri += briStep;
            if (bri > maxBrightness) {
                bri = maxBrightness;
                briStep = -1;
                nextFrameDelay(1000);

            } else if (bri < minBrightness) {
                bri = minBrightness;
                briStep = 1;
                nextFrameDelay(2000);

            } else {
                nextFrameDelay(60);
            }
            break;
    }
}

Scene *Standby::getInstance() {
    static Standby inst;
    return (Scene *) &inst;
}

