//
// Created by Oleksandr Degtiar on 29.10.2020.
//

#ifndef ZD50_DISPLAY_FONT_H
#define ZD50_DISPLAY_FONT_H

#include <avr/pgmspace.h>

/*
DotMatrix font generator
https://xantorohara.github.io/led-matrix-editor/#3c6666666666663c|7e181818181a1c18|7e76063c6060663c|3c7662603860663c|7830307e36343830|3c6e60603e06667e|3c6666663e06663c|181818183060667e|3c6666663c66663c|3c66607c6666663c
*/
const uint64_t DIGITS_1[] PROGMEM = {
        0x3c6666666666663c,
        0x7e181818181a1c18,
        0x7e76063c6060663c,
        0x3c7662603860663c,
        0x7830307e36343830,
        0x3c6e60603e06667e,
        0x3c6666663e06663c,
        0x181818183060667e,
        0x3c6666663c66663c,
        0x3c66607c6666663c
};
//https://xantorohara.github.io/led-matrix-editor/#7e7e666666667e7e|1818181818181818|7e7e067e7e607e7e|7e7e607c7c607e7e|6060607e7e666666|7e7e607e7e067e7e|7e7e667e7e067e7e|6060606060607e7e|7e7e667e7e667e7e|7e7e607e7e667e7e

//const uint64_t DIGITS_2[] PROGMEM = {
//        0x7e7e666666667e7e,
//        0x1818181818181818,
//        0x7e7e067e7e607e7e,
//        0x7e7e607c7c607e7e,
//        0x6060607e7e666666,
//        0x7e7e607e7e067e7e,
//        0x7e7e667e7e067e7e,
//        0x6060606060607e7e,
//        0x7e7e667e7e667e7e,
//        0x7e7e607e7e667e7e
//};

// https://xantorohara.github.io/led-matrix-editor/#3f3f333333333f3f|0303030303030303|3f3f033f3f303f3f|3f3f303e3e303f3f|3030303f3f333333|3f3f303f3f033f3f|3f3f333f3f033f3f|3030303030303f3f|3f3f333f3f333f3f|3f3f303f3f333f3f
const uint64_t DIGITS_2[] PROGMEM = {
        0x3f3f333333333f3f,
        0x0303030303030303,
        0x3f3f033f3f303f3f,
        0x3f3f303e3e303f3f,
        0x3030303f3f333333,
        0x3f3f303f3f033f3f,
        0x3f3f333f3f033f3f,
        0x3030303030303f3f,
        0x3f3f333f3f333f3f,
        0x3f3f303f3f333f3f
};

const uint8_t DIGITS_2_WIDTH[] = {6, 2, 6, 6, 6, 6, 6, 6, 6, 6};


// https://xantorohara.github.io/led-matrix-editor/#0037515252543700|00eea8a8aea2ee00|30383f3f3f3f3830|00333f1e1e3f3300|30383f3f3f3f3830|00001b0e0e1b0000|00383c3c3c3808f0|001c3c3c3c1c100f
const uint64_t SYMBOLS[] PROGMEM = {
        0x181c1f1f1f1f1c18, // speaker
        0x0000090606090000, // x
        0x0037515252543700,  // zd
        0x00eea8a8aea2ee00,  // 50
        0x383c3c3c3808f0e0,
        0x1c3c3c3c1c100f07,
};
const int DIGITS_LEN = sizeof(DIGITS_1) / 8;


#endif //ZD50_DISPLAY_FONT_H
