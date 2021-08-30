//
// Created by Oleksandr Degtiar on 23.02.2021.
//
#include "IR.h"
#include "ZD50.h"
#include "Display/Font.h"
#include "Menu/Menu.h"

namespace IR {

#define pinIR IR_PIN_RCV
    CNec IRLremote;

    RC_Button ButtonsDefault[RC_BUTTONS_COUNT] = {
            {
                    RC_POWER_BUTTON,
                    0x1183, 0x00
            },
            {
                    RC_VOLUME_UP_BUTTON,
                    0x1183, 0x16
            },
            {
                    RC_VOLUME_DOWN_BUTTON,
                    0x1183, 0x17
            },
            {
                    RC_MUTE_BUTTON,
                    0x1183, 0x18
            },
    };

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

    void handleRcButton(RC_Button *rc_button) {
        switch (rc_button->button) {
            case RC_POWER_BUTTON:
                break;

            case RC_VOLUME_UP_BUTTON:
                ZD50::command(Controller::Command::VOLUME_INCREMENT);
                break;

            case RC_VOLUME_DOWN_BUTTON:
                ZD50::command(Controller::Command::VOLUME_DECREMENT);
                break;

            case RC_MUTE_BUTTON:
                ZD50::command(Controller::Command::MUTE);
                break;

            default:
                break;
        }
    }

    void handleIrEvent(IR_ButtonData ir_button) {
        RC_Button *rc_button;
        rc_button = ButtonsDefault;

        ZD50::SerialOut.println(F("Lookup data:"));

        for (uint8_t i = 0; i < RC_BUTTONS_COUNT; i++, rc_button++) {
            ZD50::SerialOut.print(F("address: 0x"));
            ZD50::SerialOut.print(rc_button->ir.address, HEX);
            ZD50::SerialOut.print(F(", "));
            ZD50::SerialOut.print(F("command: 0x"));
            ZD50::SerialOut.print(rc_button->ir.command, HEX);
            ZD50::SerialOut.println();

            if (rc_button->ir.address == ir_button.address && rc_button->ir.command == ir_button.command) {
#if ZD50_DEBUG_SERIAL
                ZD50::SerialOut.print("RC button match: ");
                ZD50::SerialOut.print(rc_button->button);
                ZD50::SerialOut.println();
#endif
                handleRcButton(rc_button);
                break;
            }
        }

    }


    COROUTINE(irRcv) {
        COROUTINE_LOOP() {
            COROUTINE_AWAIT(IRLremote.available());
            // Get the new data from the remote
            auto data = IRLremote.read();

#if ZD50_DEBUG_SERIAL
            ZD50::SerialOut.print(F("IR data:"));
            ZD50::SerialOut.print(F("address: 0x"));
            ZD50::SerialOut.print(data.address, HEX);
            ZD50::SerialOut.print(F(", "));
            ZD50::SerialOut.print(F("command: 0x"));
            ZD50::SerialOut.print(data.command, HEX);
            ZD50::SerialOut.println();
#endif
            handleIrEvent(data);
            COROUTINE_DELAY(100);
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
