//
// Created by Oleksandr Degtiar on 22.10.2020.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

Controller *StandbyState::controller() {
    static const StandbyState inst;
    return (Controller *) &inst;
}

void StandbyState::begin(Controller *previousController) {
#ifdef ZD50_DEBUG_SERIAL
    ZD50::Serial.println(F("[ZD50:Standby]"));
#endif
    POWER_OFF();

    Backlight::Scene::startInstantScene(nullptr);
    ZD50::Backlight::Scene::startScene(BacklightScene::Standby::getInstance());
    Display::clear();

    if (previousController == nullptr) {
        ZD50::Attenuator::setMode(Attenuator::POWER_SAVE);
        ZD50::Attenuator::setLevel(MAX_ATTENUATION_LEVEL, false);
    }
}

void StandbyState::end() {
    Backlight::Scene::startInstantScene(nullptr);
}

void StandbyState::command(Command command, CommandParam param) {
    switch (command) {
        case Command::BUTTON_PRESS:

            switch (Button::getState()) {
                case Button::State::PRESS:
                    ZD50::setController(PoweringOnState::controller());
                    Backlight::Scene::startInstantScene(nullptr);
                    break;

                case Button::State::MIDDLE_PRESS:
                    ZD50::setController(SourcePowerOnState::controller());
                    Backlight::Scene::startInstantScene(nullptr);
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

