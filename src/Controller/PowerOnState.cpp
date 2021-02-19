//
// Created by Oleksandr Degtiar on 08.01.2021.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

Controller *PowerOnState::getInstance() {
    static const PowerOnState inst;
    return (Controller *) &inst;
}

void PowerOnState::begin(Controller *previousController) {
#ifdef ZD50_DEBUG_SERIAL
    ZD50::SerialOut.println(F("[ZD50:ON:START]"));
#endif

    POWER_ON();
    Backlight::Scene::startScene(BacklightScene::PowerOn::getInstance());
    Backlight::Scene::startInstantScene(nullptr);

    if (previousController == PoweringOffState::getInstance()) {
        // Returned from canceled powering off state

    } else {
        ZD50::Attenuator::setMode(Attenuator::NORMAL);
        ZD50::setVolume(VOLUME_START_VALUE);
    }

}

void PowerOnState::end() {
    Backlight::Scene::startInstantScene(nullptr);
}

void PowerOnState::command(Command command, CommandParam param) {
    switch (command) {
        case Command::BUTTON_PRESS:

            switch (Button::getState()) {
                case Button::State::SHORT_PRESS:
                    ZD50::setController(PoweringOffState::getInstance(), StandbyState::getInstance());
                    break;

                case Button::State::MIDDLE_PRESS:
                    ZD50::setController(PoweringOffState::getInstance(), SourcePowerOnState::getInstance());
                    break;

                default:
                    break;
            }
            break;

        case Command::BUTTON_PRESSING:
            Backlight::Scene::startInstantScene(BacklightScene::Pulse::getInstance());
            break;

        case Command::ROTATE:
            ZD50::setVolume((int) param + ZD50::getVolume());
            break;
        default:
            break;

    }

}