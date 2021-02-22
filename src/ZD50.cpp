//
// Created by Oleksandr Degtiar on 21.10.2020.
//

#include "ZD50.h"
#include "Controller/StandbyState.h"

namespace ZD50 {
#ifdef ZD50_SERIAL_HARDWARE
    HardwareSerial &SerialOut = Serial;
#else
    TinySerialOut &SerialOut = SerialOut;
#endif


    Controller *controller;

    int volume = 0;

    void init() {
#ifdef ZD50_DEBUG_SERIAL
        SerialOut.begin(38400);
        SerialOut.println(F("[ZD50:init]"));
#endif
        POWER_INIT();
        POWER_OFF();

        Backlight::init();
        Display::init();
        Display::displayWelcome();
        _delay_ms(200);
        Attenuator::init();
        Display::clear();
        setController(StandbyState::getInstance());
        Luminance::init();
        Button::init();
        Rotary::init();
    }

    Controller *getController() {
        return controller;
    }

    void setController(Controller *newController, int param) {
        if (newController == controller) {
            return;
        }
        if (controller != nullptr) {
            controller->end();
        }
        if (newController != nullptr) {
            newController->begin(controller, param);
        }
        controller = newController;
    }

    int getVolume() {
        return volume;
    }

    void setVolume(int newVolume) {
        if (newVolume > VOLUME_MAX_VALUE) {
            newVolume = VOLUME_MAX_VALUE;
        }
        if (newVolume < VOLUME_MIN_VALUE) {
            newVolume = VOLUME_MIN_VALUE;
        }
        if (volume != newVolume) {
            volume = newVolume;
            Attenuator::setLevel(VOLUME_TO_ATTENUATION_LEVEL(volume), VOLUME_TO_MUTE_STATE(volume));
        }
        Display::printVolume((uint8_t) volume);
    }

    bool handleMenuButton() {
        switch (Button::getState()) {
            case Button::SHORT_PRESS:
                menuSelect();
                break;

            case Button::MIDDLE_PRESS:
                if (!menuLeave()) {
                    menuFinish();
                    controller->onMenuClose();
                }
                break;

            case Button::LONG_PRESS:
                menuFinish();
                controller->onMenuClose();
                break;

            default:
                return false;
        }
        return true;
    }

    bool throttleMovementCommand(Controller::Command &command, int param) {
        static int value = 0;
        static unsigned long resetTime = 0;
        unsigned long now = millis();
        value = now > resetTime ? param : value + param;
        resetTime = now + 200;
        if (abs(value) > 2) {
            value = 0;
            return false;
        }
        return true;
    }

    bool handleMenuCommand(Controller::Command command, int param) {
        if (!isMenuActive()) {
            return false;
        }

        switch (command) {
            case Controller::Command::BUTTON_PRESS:
                return handleMenuButton();

            case Controller::Command::ROTATE:
                if (!isMenuEntered() && throttleMovementCommand(command, param)) {
                    return true;
                }
                if (param > 0) {
                    menuNext();
                } else if (param < 0) {
                    menuPrevious();
                }
                return true;

            default:
                return false;
        }

        return true;
    }

    void command(Controller::Command command, Controller::CommandParam param) {
        if (controller == nullptr) {
            return;
        }
#ifdef ZD50_DEBUG_COMMANDS
        SerialOut.print(F("CMD:"));
        SerialOut.print(command);
        SerialOut.print(F(":PARAM:"));
        SerialOut.print(param);
        SerialOut.println();
#endif
        if (!handleMenuCommand(command, param)) {
            controller->command(command, param);
        }
    }

    COROUTINE(controllerTick) {
        COROUTINE_LOOP() {
            COROUTINE_AWAIT(controller != nullptr);
            controller->tick();
            COROUTINE_DELAY(100);
        }
    }

    COROUTINE(liminance) {
        COROUTINE_LOOP() {
            COROUTINE_DELAY(1000);

            uint8_t brightness = 16 - (Luminance::read() >> 6);
            if (ZD50::Display::getBrightness() != brightness) {
                ZD50::Display::setBrightness(brightness);

                SerialOut.print(F("IL:"));
                SerialOut.print(Luminance::getValue());
                SerialOut.print(F(":BR:"));
                SerialOut.print(brightness);
                SerialOut.println();
            }

            static char rxChar;
            while (-1 != (rxChar = Serial.read())) {
                Serial.print(rxChar);
            }

        }
    }

}