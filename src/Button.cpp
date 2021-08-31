//
// Created by Oleksandr Degtiar on 25.01.2021.
//

#include "Button.h"
#include "ZD50.h"
#include <Arduino.h>

namespace Button {

    volatile static bool isPressed = false;
    volatile static bool isVirtuallyPressed = false;

    State state = UNPRESSED;

    static unsigned long virtualPressStartTime = 0;
    static unsigned long virtuallyPressedLastUpdated = 0;
    static unsigned long pressStartTime = 0;
    static unsigned long nextStateTime = 0;

    ISR (PCINT3_vect) {
        isPressed = BUTTON_PRESS_STATE();
    }

    unsigned long getPressingTime() {
        return state == UNPRESSED ? 0 : millis() - pressStartTime;
    }

    COROUTINE(buttonDebounce) {
        COROUTINE_LOOP() {
            static unsigned long now;

            now = millis();

            if (isVirtuallyPressed && (now - virtuallyPressedLastUpdated > VIRTUAL_PRESS_TIMEOUT)) {
                isVirtuallyPressed = false;
            }

            if (isPressed || isVirtuallyPressed) {
                if (now > nextStateTime) {
                    if (pressStartTime == 0) {
                        pressStartTime = now;
                    } else {
                        state = statesTransition[state].nextState;
                        ZD50::command(Controller::Command::BUTTON_PRESSING, state);
                    }
                    nextStateTime = now + statesTransition[state].time;
                }

            } else {
                if (state != UNPRESSED) {
                    ZD50::command(Controller::Command::BUTTON_PRESS, state);
                    pressStartTime = 0;
                    state = UNPRESSED;
                }
            }
            COROUTINE_DELAY(50);
        }
    }

    void init() {
        BUTTON_INIT_PORT();
        isPressed = BUTTON_PRESS_STATE();

        PCMSK3 |= _BV(4); // PCINT28
        PCICR |= _BV(3); // PCIE3
    }

    /**
     *
     * @return
     */
    State getState() {
        return state;
    }

    void virtualPress() {
        virtuallyPressedLastUpdated = millis();
        if (isVirtuallyPressed) {
            virtualPressStartTime = virtuallyPressedLastUpdated;
        }
        isVirtuallyPressed = true;
    }

    void virtualUnpress() {
        isVirtuallyPressed = false;
    }

}