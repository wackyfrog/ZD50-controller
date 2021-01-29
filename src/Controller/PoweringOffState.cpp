//
// Created by Oleksandr Degtiar on 11.01.2021.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

Controller *PoweringOffState::controller() {
    static const PoweringOffState inst;
    return (Controller *) &inst;
}

void PoweringOffState::begin(Controller *previousController) {
#ifdef ZD50_DEBUG_SERIAL
    ZD50::Serial.println(F("[ZD50:PoweringOffState]"));
#endif
    Backlight::Scene::startInstantScene(nullptr);
    Backlight::Scene::startScene(BacklightScene::PoweringOff::getInstance());

    POWER_SWITCHING_OFF();
    setTimeout(1000);
}

void PoweringOffState::end() {
    Backlight::Scene::startInstantScene(nullptr);
}

void PoweringOffState::command(Command command, CommandParam param) {
    switch (command) {
        case Command::TIMEOUT:
            ZD50::Attenuator::setMode(Attenuator::NORMAL);
            ZD50::Attenuator::setLevel(MAX_ATTENUATION_LEVEL, true);
            ZD50::setController(getPendingController() ?: StandbyState::controller());
            break;

        case Command::BUTTON_PRESS:
            ZD50::setController(PowerOnState::controller());
            break;

        default:
            break;

    }
}
