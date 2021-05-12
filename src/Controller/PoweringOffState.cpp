//
// Created by Oleksandr Degtiar on 11.01.2021.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"


Controller *PoweringOffState::getInstance() {
    static PoweringOffState inst;
    return (Controller *) &inst;
}

void PoweringOffState::begin(Controller *previousController, int param) {
    stopAtTime = millis() + POWERING_OFF_DURATION;
    targetState = (TargetState) param;
    Display::blink(Display::FAST);
    Backlight::Scene::stopInstantScene();
    Backlight::Scene::startScene(BacklightScene::PoweringOff::getInstance(), POWERING_OFF_DURATION);

    POWER_SWITCHING_OFF();
}

void PoweringOffState::tick() {
    if (millis() > stopAtTime) {
        ZD50::Attenuator::setMode(Attenuator::NORMAL);
        ZD50::Attenuator::setLevel(MAX_ATTENUATION_LEVEL, true);

        switch (targetState) {
            case PowerOnSource:
                ZD50::setController(SourcePowerOnState::getInstance());
                break;

            case StandBy:
            default:
                ZD50::setController(StandbyState::getInstance());
        }
    }
}

void PoweringOffState::end() {
    Display::blink(Display::NONE);
    Backlight::Scene::stopInstantScene();
}

void PoweringOffState::command(Command command, CommandParam param) {
    switch (command) {
        case Command::BUTTON_PRESS:
            ZD50::setController(PowerOnState::getInstance());
            break;

        default:
            break;

    }
}
