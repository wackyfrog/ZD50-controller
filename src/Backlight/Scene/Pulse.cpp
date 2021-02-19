//
// Created by Oleksandr Degtiar on 26.01.2021.
//

#include "Backlight.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

using namespace Backlight;
using namespace BacklightScene;

static uint8_t state = 0;
static int bri;
static int briStep;
static const int minBrightness = 0;
static const int maxBrightness = 100;

void Pulse::begin() {
    state = 0;
}


void Pulse::frame() {
    switch (state) {
        case 0:
            bri = 10;
            briStep = -1;
            state++;
            break;

        case 1:
            fill((Backlight::cRGB) {(uint8_t) bri, (uint8_t) bri, 0});
            Backlight::update();
            bri -= 1;
/*
            if (bri > maxBrightness) {
                bri = maxBrightness;
                briStep = -1;
                nextFrameDelay(1000);
                break;
            }
*/
            if (bri < 0) {
                state = 2;
                nextFrameDelay(2000);
                break;
            }

            nextFrameDelay(10);
            break;

        case 2:

            done();
            break;
    }

}


Scene *Pulse::getInstance() {
    static Pulse inst;
    return (Scene *) &inst;
}
