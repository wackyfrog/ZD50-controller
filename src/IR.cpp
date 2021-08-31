//
// Created by Oleksandr Degtiar on 23.02.2021.
//
#include "IR.h"
#include "ZD50.h"
#include "Display/Font.h"
#include "Menu/Menu.h"

#define IR_REPEAT_ADDR ( 0xffff )
#define IR_REPEAT_CMD ( 0x00 )
namespace IR {

#define pinIR IR_PIN_RCV
    CNec IRLremote;

    void init() {
#if ZD50_DEBUG_SERIAL
        ZD50::SerialOut.println(F("[IR:init]"));
#endif
        IR_ENABLE();

        if (!IRLremote.begin(pinIR)) {
#if ZD50_DEBUG_SERIAL
            ZD50::SerialOut.println(F("IR ISR attach fail."));
#endif
        }
    }

    void handleRcButton(RC_Button *rc_button, unsigned long pressingTime) {
        switch (rc_button->button) {
            case RC_POWER_BUTTON:
                Button::virtualPress();
                break;

            case RC_VOLUME_UP_BUTTON:
                if (pressingTime == 0 || pressingTime > RC_REPEAT_DELAY) {
                    ZD50::command(Controller::Command::VOLUME_INCREMENT);
                }
                break;

            case RC_VOLUME_DOWN_BUTTON:
                if (pressingTime == 0 || pressingTime > RC_REPEAT_DELAY) {
                    ZD50::command(Controller::Command::VOLUME_DECREMENT);
                }
                break;

            case RC_MUTE_BUTTON:
                if (pressingTime == 0) {
                    ZD50::command(Controller::Command::MUTE);
                }
                break;

            default:
                break;
        }
    }

    void handleIrEvent(IR_ButtonData irButton) {
        unsigned long now = millis();
        static unsigned long pressTime = 0;
        static IR_ButtonData lastPressedIrButton;

        if (irButton.address == IR_REPEAT_ADDR && irButton.command == IR_REPEAT_CMD) {
            irButton = lastPressedIrButton;
        } else {
            lastPressedIrButton = irButton;
            pressTime = now;
        }


#if ZD50_DEBUG_SERIAL
        ZD50::SerialOut.print(F("[IR] "));
        ZD50::SerialOut.print(F("addr: 0x"));
        ZD50::SerialOut.print(irButton.address, HEX);
        ZD50::SerialOut.print(F(", "));
        ZD50::SerialOut.print(F("cmd: 0x"));
        ZD50::SerialOut.print(irButton.command, HEX);
        ZD50::SerialOut.print(F(", ms: "));
        ZD50::SerialOut.print((int32_t)(now - pressTime));
        ZD50::SerialOut.println();
#endif

        RC_Button *rcButton = (RC_Button *)ButtonsDefault;
        for (uint8_t i = 0; i < RC_BUTTONS_COUNT; i++, rcButton++) {
            if (rcButton->ir.address == irButton.address && rcButton->ir.command == irButton.command) {
#if ZD50_DEBUG_SERIAL
                ZD50::SerialOut.print("[RC] button ID: ");

                ZD50::SerialOut.print(rcButton->button);
                ZD50::SerialOut.println();
#endif
                handleRcButton(rcButton, now - pressTime);
                break;
            }
        }

    }


    COROUTINE(irRcv) {
        COROUTINE_LOOP() {
            COROUTINE_AWAIT(IRLremote.available());
            handleIrEvent(IRLremote.read());
            COROUTINE_DELAY(10);
        }
    }

}


// ---------------------------------------
static void adjust(Menu::Id id, int value) {
#if ZD50_DEBUG_MENU
    ZD50::SerialOut.println(F("IR adj callback"));
#endif
}

static void onMenuSelect(Menu::Id id) {
//    Display::printBitmap(4, 0, &Font::IMG_IR);
#if ZD50_DEBUG_MENU
    ZD50::SerialOut.print(F("[MENU_SELECT:"));
    ZD50::SerialOut.print(id);
    ZD50::SerialOut.println(F("]"));
#endif
}

static void onMenuEnter(Menu::Id id) {
#if ZD50_DEBUG_MENU
    ZD50::SerialOut.print(F("[MENU_ENTER:"));
    ZD50::SerialOut.print(id);
    ZD50::SerialOut.println(F("]"));
#endif
}

MENU_ITEM(MenuIR, Menu::IR,
          MENU_NULL, MENU_NULL, MENU_NULL, MENU_NULL,
          onMenuSelect,
          onMenuEnter,
          adjust
);

//Menu::Item *IR::getMenu() {
//    return &MenuIR;
//}
