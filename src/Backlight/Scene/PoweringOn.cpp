//
// Created by Oleksandr Degtiar on 26.01.2021.
//

#include "Backlight.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

using namespace Backlight;
using namespace BacklightScene;

static uint8_t state = 0;
//static int bri;
//static int briStep;
static const int minBrightness = 0;
static const int maxBrightness = 4;

void PoweringOn::begin() {
    state = 0;
}

#define LED_INDEX(i) (i < 10 ? i + 2 : i - 10)

void PoweringOn::frame() {

    switch (state) {
        case 13:
            state++;
            nextFrameDelay(10);
            return;

        case 14:
            Backlight::fill((Backlight::cRGB) {0, 0, 0});
            Backlight::update();
            done();
            return;
    }

    Backlight::fill((Backlight::cRGB) {0, 0, 0});
    cRGB color = (Backlight::cRGB) {50, 50, 50};

    for (uint8_t index = 0; index < state; ++index) {
        Backlight::setPixel(LED_INDEX(index), color);
    }
    Backlight::update();
    ++state;
    nextFrameDelay(160);

}

Scene *PoweringOn::getInstance() {
    static PoweringOn inst;
    return (Scene *) &inst;
}
