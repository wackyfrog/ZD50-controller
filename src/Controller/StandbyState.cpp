//
// Created by Oleksandr Degtiar on 22.10.2020.
//

#include "Controller/States.h"
#include "Backlight/Scenes.h"
#include "ZD50.h"
#include "Display/Font.h"
#include "Menu/Menu.h"


MENU_ITEM(MenuBrightness, Menu::Brightness,
          MENU_NULL, MenuHue, MENU_NULL, MENU_NULL,
          StandbyState::onMenuSelect,
          StandbyState::onMenuEnter,
          StandbyState::onMenuItemChange);

MENU_ITEM(MenuHue, Menu::Hue,
          MenuBrightness, MenuSaturation, MENU_NULL, MENU_NULL,
          StandbyState::onMenuSelect,
          StandbyState::onMenuEnter,
          StandbyState::onMenuItemChange);

MENU_ITEM(MenuSaturation, Menu::Saturation,
          MenuHue, MENU_NULL, MENU_NULL, MENU_NULL,
          StandbyState::onMenuSelect,
          StandbyState::onMenuEnter,
          StandbyState::onMenuItemChange);

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
                    break;

                case Button::State::LONG_PRESS:
                    select(&MenuBrightness);
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


void StandbyState::onMenuClose() {
    Serial.println(F("[MENU_CLOSE]"));
    Display::clear();
}

void StandbyState::onMenuSelect(Menu::Id id) {
    Serial.print(F("[MENU_SELECT:"));
    Serial.print(id);
    Serial.println(F("]"));
}

void StandbyState::onMenuEnter(Menu::Id id) {
    Serial.print(F("[MENU_ENTER:"));
    Serial.print(id);
    Serial.println(F("]"));
}

void StandbyState::onMenuItemChange(Menu::Id id, int value) {
    Serial.print(F("[ADJ:"));
    Serial.print(id);
    Serial.print(F(":"));
    Serial.print(value);
    Serial.println(F("]"));
}

