//
// Created by Oleksandr Degtiar on 23.02.2021.
//

#include "IR.h"
#include "ZD50.h"
#include "Display/Font.h"
#include "Menu/Menu.h"
#include <IRLremote.h>

#define pinIR 2
CNec IRLremote;



//#define IR_SMALLD_RC5

//#include <IRsmallDecoder.h>

//static irSmallD_t irData;
/*
void irISR() {
//    ZD50::SerialOut.println(F("IR"));
    if (IRsmallDecoder::_irDataAvailable) {
        IRsmallDecoder::dataAvailable(irData);
        ZD50::SerialOut.print(F("IR key:"));
        ZD50::SerialOut.print(irData.keyHeld, HEX);
        ZD50::SerialOut.print(F(" addr:"));
        ZD50::SerialOut.print(irData.addr, HEX);
        ZD50::SerialOut.print(F(" cmd:"));
        ZD50::SerialOut.println(irData.cmd, HEX);
    }
}
*/

void IR::init() {
#if ZD50_DEBUG_SERIAL
    ZD50::SerialOut.println(F("[IR:init]"));
#endif
    IR_ENABLE();

    if (!IRLremote.begin(pinIR)) {
#if ZD50_DEBUG_SERIAL
        ZD50::SerialOut.println(F("IR ISR attach fail."));
#endif
    }

//    attachInterrupt(2, IRsmallDecoder::irISR, IR_ISR_MODE);
}

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

COROUTINE(irRcv) {
    COROUTINE_LOOP() {
#if ZD50_DEBUG_SERIAL
        ZD50::SerialOut.println(F("IR loop"));
#endif
        COROUTINE_AWAIT(IRLremote.available());
        // Get the new data from the remote
        auto data = IRLremote.read();

#if ZD50_DEBUG_SERIAL
        // Print the protocol data
        ZD50::SerialOut.print(F("Address: 0x"));
        ZD50::SerialOut.println(data.address, HEX);
        ZD50::SerialOut.print(F("Command: 0x"));
        ZD50::SerialOut.println(data.command, HEX);
        ZD50::SerialOut.println();
#endif
        COROUTINE_DELAY(1);
    }
}
//Menu::Item *IR::getMenu() {
//    return &MenuIR;
//}
