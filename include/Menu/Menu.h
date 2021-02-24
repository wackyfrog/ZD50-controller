//
// Created by Oleksandr Degtiar on 21.02.2021.
//

#ifndef ZD50_CONTROLLER_MENU_H
#define ZD50_CONTROLLER_MENU_H

#include <stdint.h>

namespace Menu {
    typedef enum : uint8_t {
        Exit = 0,
        Brightness, Hue, Saturation,
        IR,
    } Id;

    typedef void(SelectCallback)(Id id);

    typedef void(EnterCallback)(Id id);

    typedef void(ChangeCallback)(Id id, int value);

    typedef const struct ItemStruct {
        const Id id;
        const struct ItemStruct *previous;
        const struct ItemStruct *next;
        const struct ItemStruct *parent;
        const struct ItemStruct *child;
        SelectCallback *onSelect;
        EnterCallback *onEnter;
        ChangeCallback *onChange;
    } Item;

    bool select(const Item *newMenu);

    bool select();

    bool leave();

    bool next();

    bool previous();

    bool isActive();

    bool isEntered();

    void finish();

    extern const Item _EMPTY;
}
#define MENU_NULL (Menu::_EMPTY)

#define MENU_ITEM(name, id, previous, next, parent, child, onSelect, onEnter, onChange) \
    extern Menu::Item PROGMEM previous; \
    extern Menu::Item PROGMEM next;     \
    extern Menu::Item PROGMEM parent;   \
    extern Menu::Item PROGMEM child;  \
    Menu::Item name = {id, &previous, &next, &parent, &child, &onSelect, &onEnter, &onChange}

#endif //ZD50_CONTROLLER_MENU_H
