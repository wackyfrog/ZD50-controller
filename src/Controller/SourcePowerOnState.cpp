//
// Created by Oleksandr Degtiar on 08.01.2021.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

Controller *SourcePowerOnState::controller() {
    static const SourcePowerOnState inst;
    return (Controller *) &inst;
}

void SourcePowerOnState::begin(Controller *previousController) {
#ifdef ZD50_DEBUG_SERIAL
    ZD50::Serial.println(F("[ZD50:SRC_ON:START]"));
#endif

    POWER_ON_SOURCE_ONLY();
    ZD50::Display::displayHeadphones();
    Backlight::Scene::startScene(BacklightScene::SourcePowerOn::getInstance());
    Backlight::Scene::startInstantScene(nullptr);
}

void SourcePowerOnState::end() {
    Backlight::Scene::startInstantScene(nullptr);
}

void SourcePowerOnState::command(Command command, CommandParam param) {
    switch (command) {
        case Command::BUTTON_PRESS:

            switch (Button::getState()) {
                case Button::State::PRESS:
                    ZD50::setController(PoweringOnState::controller());
                    Backlight::Scene::startInstantScene(nullptr);
                    break;

                case Button::State::MIDDLE_PRESS:
                    ZD50::setController(StandbyState::controller());
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