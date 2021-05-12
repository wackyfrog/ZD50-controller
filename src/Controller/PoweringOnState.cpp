//
// Created by Oleksandr Degtiar on 11.01.2021.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

Controller *PoweringOnState::getInstance() {
    static PoweringOnState inst;
    return (Controller *) &inst;
}

void PoweringOnState::begin(Controller *previousController, int param) {
    stopAtTime = millis() + 2000;

    Backlight::Scene::startScene(BacklightScene::PoweringOn::getInstance());
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
    if (millis() > stopAtTime) {
        ZD50::setController(PowerOnState::getInstance());
    }
}

void PoweringOnState::end() {
    Backlight::Scene::stopInstantScene();
}

