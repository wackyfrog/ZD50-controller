//
// Created by Oleksandr Degtiar on 07.01.2021.
//

#include "Backlight.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

using namespace Backlight;
using namespace BacklightScene;

static uint8_t state = 0;
static int bri;
//static int briStep;
static const int minBrightness = 0;
static const int maxBrightness = 4;

void PowerOn::begin() {
    ZD50::Serial.println(F("[PowerOnScene::begin]"));
    state = 0;
}

void PowerOn::frame() {
    fill((Backlight::cRGB) {1, 1, 1});
    Backlight::update();
    done();
    return;

    switch (state) {
        case 0:
            bri = 0;
            state++;
            break;

        case 1:
            fill((Backlight::cRGB) {(uint8_t) bri, 0, 0});
            Backlight::update();
            bri += 1;

            if (bri > 10) {
                state = 2;
                break;
            }

            nextFrameDelay(100);
            break;

        case 2:

            done();
            break;
    }

}

Scene *PowerOn::getInstance() {
    static PowerOn inst;
    return (Scene *) &inst;
}
