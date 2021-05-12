//
// Created by Oleksandr Degtiar on 08.01.2021.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"

Controller *SourcePowerOnState::getInstance() {
    static SourcePowerOnState inst;
    return (Controller *) &inst;
}

void SourcePowerOnState::begin(Controller *previousController, int param) {
#if ZD50_DEBUG_SERIAL
    ZD50::SerialOut.println(F("[ZD50:SRC_ON:START]"));
#endif

    POWER_ON_SOURCE_ONLY();
    ZD50::Display::displayHeadphones();
    Backlight::Scene::startScene(BacklightScene::SourcePowerOn::getInstance());
    Backlight::Scene::stopInstantScene();
}

void SourcePowerOnState::end() {
    Backlight::Scene::stopInstantScene();
}

void SourcePowerOnState::command(Command command, CommandParam param) {
    switch (command) {
        case Command::BUTTON_PRESS:

            switch (Button::getState()) {
                case Button::State::SHORT_PRESS:
                    ZD50::setController(PoweringOnState::getInstance());
                    Backlight::Scene::stopInstantScene();
                    break;

                case Button::State::MIDDLE_PRESS:
                    ZD50::setController(StandbyState::getInstance());
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
