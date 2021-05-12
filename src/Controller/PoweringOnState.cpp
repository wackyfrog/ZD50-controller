//
// Created by Oleksandr Degtiar on 11.01.2021.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

static int dotStep = 0;
static unsigned long stopAtTime = 0;
static uint32_t stateDuration;
static uint32_t frameDelay;

#define DOTS_UP 4
#define DOTS_LEN 16

Controller *PoweringOnState::getInstance() {
    static PoweringOnState inst;
    return (Controller *) &inst;
}

void PoweringOnState::begin(Controller *previousController, int param) {
    dotStep = 0;

    stateDuration =
            previousController == SourcePowerOnState::getInstance() ? FAST_SOFT_START_DURATION : SOFT_START_DURATION;

    frameDelay = stateDuration / (uint32_t) (DOTS_UP * (DOTS_LEN + 1));

    stopAtTime = millis() + stateDuration;
    Backlight::Scene::startScene(BacklightScene::PoweringOn::getInstance(), stateDuration);

    Display::operate();
    Display::clear();

    if (IS_MAIN_POWER_ON()) {
        ZD50::Attenuator::setMode(Attenuator::NORMAL);

    } else {
#if ZD50_DEBUG_SERIAL
        ZD50::SerialOut.println(F("[REFRESHING]"));
#endif
        ZD50::Attenuator::setMode(Attenuator::POWER_SAVE);
        ZD50::Attenuator::setLevel(MIN_ATTENUATION_LEVEL, true);
    }

    ZD50::Attenuator::setLevel(MAX_ATTENUATION_LEVEL, true);
    POWER_SWITCHING_ON();
}

void PoweringOnState::tick() {
    const unsigned long now = millis();
    static unsigned long frameWait = 0;
    if (now > stopAtTime) {
        ZD50::setController(PowerOnState::getInstance());
    } else {
        if (now > frameWait) {
            frame();
            frameWait = now + frameDelay;
        }
    }
}

void PoweringOnState::frame() const {
    static int col = 0;
    static uint8_t colByte = 0;
    static uint8_t counterUp = 0;

    if (dotStep == 0) {
        col = 0;
        colByte = 0;
        counterUp = 0;
        dotStep++;

    } else if (dotStep == -1) {
        return;
    }

    if (counterUp >= DOTS_UP) {
        colByte = 0;
        counterUp = 0;
        ++col;
        if (col > DOTS_LEN - 1) {
            dotStep = -1;
            return;
        }
    } else {
        colByte <<= 1;
    }
    colByte |= 1;
    counterUp++;

    Display::col(col, colByte);
    Display::flushBuffer();
}

void PoweringOnState::end() {
    Backlight::Scene::stopInstantScene();
}

