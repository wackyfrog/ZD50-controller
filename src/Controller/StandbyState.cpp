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
          StandbyState::settingLightnessMaxAdjust);

MENU_ITEM(MenuHue, Menu::Hue,
          MenuBrightness, MenuSaturation, MENU_NULL, MENU_NULL,
          StandbyState::onMenuSelect,
          StandbyState::onMenuEnter,
          StandbyState::settingHueAdjust);

MENU_ITEM(MenuSaturation, Menu::Saturation,
          MenuHue, MENU_NULL, MENU_NULL, MENU_NULL,
          StandbyState::onMenuSelect,
          StandbyState::onMenuEnter,
          StandbyState::settingSaturationAdjust);

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
                    Menu::select(&MenuBrightness);
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
    Display::blink(Display::NONE);
#ifdef ZD50_DEBUG_MENU
    Serial.println(F("[MENU_CLOSE]"));
#endif

    Display::clear();
    Backlight::Scene::getInstance()->setNormalMode();
}

void StandbyState::onMenuSelect(Menu::Id id) {
#ifdef ZD50_DEBUG_MENU
    Serial.print(F("[MENU_SELECT:"));
    Serial.print(id);
    Serial.println(F("]"));
#endif
    Display::blink(Display::NONE);
    Display::clearBuffer();
    Backlight::Scene::stopInstantScene();
    Backlight::Scene::getInstance()->setPreviewMode();
    switch (id) {
        case Menu::Brightness:
            Display::printBitmap(4, 0, &Font::IMG_BRIGHTNESS);
            break;

        case Menu::Hue:
            Display::printBitmap(4, 0, &Font::IMG_HUE);
            break;

        case Menu::Saturation:
            Display::printBitmap(4, 0, &Font::IMG_SATURATION);
            break;

        default:
            break;
    }

    Display::flushBuffer();
}

void StandbyState::onMenuEnter(Menu::Id id) {
#ifdef ZD50_DEBUG_MENU
    Serial.print(F("[MENU_ENTER:"));
    Serial.print(id);
    Serial.println(F("]"));
#endif
    Display::blink(Display::FAST);

    Backlight::Scene::stopInstantScene();
    Backlight::Scene::getInstance()->setPreviewMode();
}

void StandbyState::settingLightnessMaxAdjust(Menu::Id id, int value) {
    BacklightScene::Standby *pStandby = (BacklightScene::Standby *) BacklightScene::Standby::getInstance();
    Display::print(
            pStandby->setLightnessMax(pStandby->getLightnessMax() + value)
    );
}

void StandbyState::settingHueAdjust(Menu::Id id, int value) {
    BacklightScene::Standby *pStandby = (BacklightScene::Standby *) BacklightScene::Standby::getInstance();
    Display::print(
            360 * ((long) pStandby->setHue(pStandby->getHue() + ((long) value) * 4)) / HSV_HUE_MAX
    );
}

void StandbyState::settingSaturationAdjust(Menu::Id id, int value) {
    BacklightScene::Standby *pStandby = (BacklightScene::Standby *) BacklightScene::Standby::getInstance();
    Display::print(
            100 * (
                    pStandby->setSaturation(pStandby->getSaturation() + value * 10)
            ) / HSV_SAT_MAX
    );
}
