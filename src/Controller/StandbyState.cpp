//
// Created by Oleksandr Degtiar on 22.10.2020.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

Controller *StandbyState::getInstance() {
    static StandbyState inst;
    return (Controller *) &inst;
}

void StandbyState::begin(Controller *previousController, int param) {
#ifdef ZD50_DEBUG_SERIAL
    ZD50::SerialOut.println(F("[ZD50:Standby]"));
#endif
    POWER_OFF();

    Backlight::Scene::stopInstantScene();
    ZD50::Backlight::Scene::startScene(BacklightScene::Standby::getInstance());
    Display::clear();

    if (previousController == nullptr) {
        ZD50::Attenuator::setMode(Attenuator::POWER_SAVE);
        ZD50::Attenuator::setLevel(MAX_ATTENUATION_LEVEL, false);
    }
}

void StandbyState::end() {
    Backlight::Scene::stopInstantScene();
}

void StandbyState::command(Command command, CommandParam param) {
    switch (command) {
        case Command::BUTTON_PRESS:

            switch (Button::getState()) {
                case Button::State::SHORT_PRESS:
                    ZD50::setController(PoweringOnState::getInstance());
                    Backlight::Scene::stopInstantScene();
                    break;

                case Button::State::MIDDLE_PRESS:
                    ZD50::setController(SourcePowerOnState::getInstance());
                    Backlight::Scene::stopInstantScene();
                    break;

                default:
                    break;
            }
            break;

        case Command::BUTTON_PRESSING:
            Backlight::Scene::startInstantScene(BacklightScene::Pulse::getInstance());
            break;

        default:
            break;

    }
}

