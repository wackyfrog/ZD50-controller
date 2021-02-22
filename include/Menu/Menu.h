//
// Created by Oleksandr Degtiar on 21.02.2021.
//

#ifndef ZD50_CONTROLLER_MENU_H
#define ZD50_CONTROLLER_MENU_H

#include <stdint.h>

typedef enum : uint8_t {
    Exit = 0,
    Brightness, Hue, Saturation
} MenuId;

typedef void(MenuCallback)(MenuId id);

typedef void(MenuChangeCallback)(MenuId id, int value);

typedef const struct MenuItemStruct {
    const MenuId id;
    const struct MenuItemStruct *previous;
    const struct MenuItemStruct *next;
    const struct MenuItemStruct *parent;
    const struct MenuItemStruct *child;
    MenuCallback *onSelect;
    MenuCallback *onEnter;
    MenuChangeCallback *onChange;
} MenuItem;

bool menuSelect(const MenuItem *newMenu);

bool menuSelect();

bool menuLeave();

bool menuNext();

bool menuPrevious();

bool isMenuActive();

bool isMenuEntered();

void menuFinish();


extern const MenuItem MENU_NULL_;
#define MENU_NULL MENU_NULL_

#define MENU_ITEM(name, id, previous, next, parent, child, onSelect, onEnter, onChange) \
    extern MenuItem PROGMEM previous; \
    extern MenuItem PROGMEM next;     \
    extern MenuItem PROGMEM parent;   \
    extern MenuItem PROGMEM child;  \
    MenuItem name = {id, &previous, &next, &parent, &child, &onSelect, &onEnter, &onChange}

#endif //ZD50_CONTROLLER_MENU_H
