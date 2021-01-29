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
static const int maxBrightness = 5;

void SourcePowerOn::begin() {
    ZD50::Serial.println(F("[SourcePowerOnScene::begin]"));
    state = 0;
}

void SourcePowerOn::frame() {

    switch (state) {
        case 0:
            bri = 0;
            state++;
            break;

        case 1:
            fill((Backlight::cRGB) {0, 0, (uint8_t) bri});
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

Scene *SourcePowerOn::getInstance() {
    static SourcePowerOn inst;
    return (Scene *) &inst;
}
