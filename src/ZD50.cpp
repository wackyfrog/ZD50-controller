//
// Created by Oleksandr Degtiar on 21.10.2020.
//

#include "ZD50.h"
#include "Controller/StandbyState.h"

TinySerialOut ZD50::Serial = SerialOut;

namespace ZD50 {
    Controller *controller;

    int volume = 0;

    void init() {
#ifdef ZD50_DEBUG_SERIAL
        Serial.begin(0);
        Serial.println(F("[ZD50:init]"));
#endif
        POWER_INIT();
        POWER_OFF();

        Backlight::init();
        Display::init();
        Display::displayWelcome();
        _delay_ms(200);
        Attenuator::init();
        Display::clear();
        setController(StandbyState::controller());
        Luminance::init();
        Button::init();
        Rotary::init();
    }

    Controller *getController() {
        return controller;
    }

    void setController(Controller *newController, Controller *pendingtController) {
        if (newController == controller) {
            return;
        }
        if (controller != nullptr) {
            controller->end();
        }
        if (newController != nullptr) {
            newController->setPendingController(pendingtController);
            newController->begin(controller);
        }
        controller = newController;
    }

    int getVolume() {
        return volume;
    }

    void setVolume(int newVolume) {
        ZD50::Serial.println(newVolume);
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

    COROUTINE(controllerTick) {
        COROUTINE_LOOP() {
            COROUTINE_DELAY(100);
            COROUTINE_AWAIT(controller != nullptr && controller->isTimeoutActive());
            if (controller->isTimeoutExpired()) {
                controller->command(Controller::Command::TIMEOUT, 0);
            }
            COROUTINE_DELAY(100);
        }
    }
}