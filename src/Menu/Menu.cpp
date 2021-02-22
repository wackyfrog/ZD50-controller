//
// Created by Oleksandr Degtiar on 21.02.2021.
//

#include <Arduino.h>
#include "Menu/Menu.h"
#include "ZD50.h"

const MenuItem MENU_NULL = {Exit, NULL, NULL, NULL, NULL,
                            NULL, NULL, NULL};

static MenuItem *selected = &MENU_NULL;
static MenuItem *entered = &MENU_NULL;


bool menuItemAdjustValue(int value);


bool menuNext() {
    if (isMenuEntered()) {
        return menuItemAdjustValue(1);

    } else {
        return menuSelect((MenuItem *) pgm_read_word(&selected->next));
    }
}

bool menuPrevious() {
    if (isMenuEntered()) {
        return menuItemAdjustValue(-1);
    } else {
        return menuSelect((MenuItem *) pgm_read_word(&selected->previous));
    }
}

bool menuItemAdjustValue(int value) {
    MenuChangeCallback *callback = (MenuChangeCallback *) pgm_read_word(&selected->onChange);
    if (callback) {
        callback(static_cast<MenuId>(pgm_read_byte(&selected->id)), value);
        return true;
    }
    return false;
}

bool menuLeave() {
    if (isMenuEntered()) {
        entered = &MENU_NULL;
        return menuSelect(selected);
    }
    return menuSelect((MenuItem *) pgm_read_word(&selected->parent));
}

bool menuSelect(const MenuItem *newMenu) {
    if (newMenu == &MENU_NULL || newMenu == NULL) {
        return false;
    }
    selected = newMenu;
    MenuCallback *callback = (MenuCallback *) pgm_read_word(&selected->onSelect);

    if (callback) {
        callback(static_cast<MenuId>(pgm_read_byte(&selected->id)));
    }
    return true;
}


bool menuSelect() {
    if (menuSelect((MenuItem *) pgm_read_word(&selected->child))) {
        return false;
    }

    if (isMenuEntered() && entered == selected) {
        return menuLeave();
    }

    MenuCallback *callback = (MenuCallback *) pgm_read_word(&selected->onEnter);

    if (callback) {
        entered = selected;
        callback(static_cast<MenuId>(pgm_read_byte(&selected->id)));
    }
    return true;
}

bool isMenuActive() {
    return !(selected == &MENU_NULL || selected == NULL);
}

bool isMenuEntered() {
    return !(entered == &MENU_NULL || entered == NULL);
}

void menuFinish() {
    entered = &MENU_NULL;
    selected = &MENU_NULL;
}
