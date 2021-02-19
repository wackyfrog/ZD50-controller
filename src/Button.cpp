//
// Created by Oleksandr Degtiar on 25.01.2021.
//

#include "Button.h"
#include "ZD50.h"
#include <Arduino.h>

namespace Button {

    static bool isPressed = false;

    State state = UNPRESSED;

    static unsigned long pressStartedMillis = 0;

    ISR (PCINT3_vect) {
        isPressed = BUTTON_PRESS_STATE();
    }

    unsigned long getPressingTime() {
        return state == UNPRESSED ? 0 : millis() - pressStartedMillis;
    }


    COROUTINE(buttonDebounce) {
        COROUTINE_LOOP() {
            COROUTINE_AWAIT(isPressed);
            COROUTINE_DELAY(statesTransition[state].time);
            if (isPressed) {
                state = SHORT_PRESS;
                pressStartedMillis = millis();
            }
            COROUTINE_AWAIT(!isPressed);
        }
    }

    COROUTINE(buttonLogic) {
        COROUTINE_LOOP() {
//            using namespace StateController;
            static unsigned long pressingTime = 0;
            static unsigned long nextUpdateTime = 0;

            COROUTINE_AWAIT(state != UNPRESSED);

            if (isPressed) {
                pressingTime = getPressingTime();
                if (pressingTime > statesTransition[state].time) {
                    if (statesTransition[state].nextState != state) {
                        state = statesTransition[state].nextState;
                    }
                }

                if (/*pressingTime > statesTransition[state].time &&*/ pressingTime > nextUpdateTime) {
                    ZD50::command(Controller::Command::BUTTON_PRESSING, state);
                    nextUpdateTime = pressingTime + statesTransition[state].time;
                }

            } else {
                ZD50::command(Controller::Command::BUTTON_PRESS, state);
                pressStartedMillis = 0;
                nextUpdateTime = 0;
                state = UNPRESSED;
            }
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

}