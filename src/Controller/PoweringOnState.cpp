//
// Created by Oleksandr Degtiar on 11.01.2021.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

Controller *PoweringOnState::getInstance() {
    static const PoweringOnState inst;
    return (Controller *) &inst;
}

void PoweringOnState::begin(Controller *previousController) {
#ifdef ZD50_DEBUG_SERIAL
    SerialOut.println(F("[ZD50:PoweringOnState]"));
#endif
    Backlight::Scene::startInstantScene(nullptr);
    Backlight::Scene::startScene(BacklightScene::PoweringOn::getInstance());
    Display::clear();

    if (IS_MAIN_POWER_ON()) {
        ZD50::Attenuator::setMode(Attenuator::NORMAL);
        ZD50::Attenuator::setLevel(MAX_ATTENUATION_LEVEL, true);

    } else {
        SerialOut.println(F("[REFRESHING]"));
        ZD50::Attenuator::setMode(Attenuator::POWER_SAVE);
        ZD50::Attenuator::setLevel(MIN_ATTENUATION_LEVEL, true);
        ZD50::Attenuator::setLevel(MAX_ATTENUATION_LEVEL, true);
    }

    POWER_SWITCHING_ON();
    setTimeout(2000);
}

void PoweringOnState::end() {
    Backlight::Scene::startInstantScene(nullptr);
}

void PoweringOnState::command(Command command, CommandParam param) {
    switch (command) {
        case Command::TIMEOUT:
            ZD50::setController(PowerOnState::getInstance());
            break;

        default:
            break;

    }
}
