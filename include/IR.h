//
// Created by Oleksandr Degtiar on 23.02.2021.
//

#ifndef ZD50_CONTROLLER_IR_H
#define ZD50_CONTROLLER_IR_H

#include "ZD50.h"
#include "Menu/Menu.h"
namespace IR {
    void init();
    Menu::Item* getMenu();

}
//extern Menu::Item MenuIR;
#endif //ZD50_CONTROLLER_IR_H
