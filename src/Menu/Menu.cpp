//
// Created by Oleksandr Degtiar on 21.02.2021.
//

#include <Arduino.h>
#include "Menu/Menu.h"
#include "ZD50.h"

namespace Menu {

    const Item _EMPTY = {Exit, NULL, NULL, NULL, NULL,
                         NULL, NULL, NULL};

    static Item *selected = &MENU_NULL;
    static Item *entered = &MENU_NULL;


    bool menuItemAdjustValue(int value);


    bool next() {
        if (isEntered()) {
            return menuItemAdjustValue(1);

        } else {
            return select((Item *) pgm_read_word(&selected->next));
        }
    }

    bool previous() {
        if (isEntered()) {
            return menuItemAdjustValue(-1);
        } else {
            return select((Item *) pgm_read_word(&selected->previous));
        }
    }

    bool menuItemAdjustValue(int value) {
        ChangeCallback *callback = (ChangeCallback *) pgm_read_word(&selected->onChange);
        if (callback) {
            callback(static_cast<Id>(pgm_read_byte(&selected->id)), value);
            return true;
        }
        return false;
    }

    bool leave() {
        if (isEntered()) {
            entered = &MENU_NULL;
            return select(selected);
        }
        return select((Item *) pgm_read_word(&selected->parent));
    }

    bool select(const Item *newMenu) {
        if (newMenu == &MENU_NULL || newMenu == NULL) {
            return false;
        }
        selected = newMenu;
        SelectCallback *callback = (SelectCallback *) pgm_read_word(&selected->onSelect);

        if (callback) {
            callback(static_cast<Id>(pgm_read_byte(&selected->id)));
        }
        return true;
    }


    bool select() {
        if (Menu::select((Item *) pgm_read_word(&selected->child))) {
            return false;
        }

        if (isEntered() && entered == selected) {
            return leave();
        }

        EnterCallback *callback = (EnterCallback *) pgm_read_word(&selected->onEnter);

        if (callback) {
            entered = selected;
            callback(static_cast<Id>(pgm_read_byte(&selected->id)));
        }
        return true;
    }

    bool isActive() {
        return !(selected == &MENU_NULL || selected == NULL);
    }

    bool isEntered() {
        return !(entered == &MENU_NULL || entered == NULL);
    }

    void finish() {
        entered = &MENU_NULL;
        selected = &MENU_NULL;
    }
}
