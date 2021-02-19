//
// Created by Oleksandr Degtiar on 29.10.2020.
//

#ifndef ZD50_DISPLAY_FONT_H
#define ZD50_DISPLAY_FONT_H

#include <avr/pgmspace.h>

typedef const uint64_t FontBitmap PROGMEM;

typedef const char CharWidth;


/*

enum Fonts {
    Digits1,
    MAX_FONTS
};
*/

/*
DotMatrix font generator
https://xantorohara.github.io/led-matrix-editor/#3e6363636363633e|7e181818181a1c18|7f6306083060633e|3e6360603860633e|7830307f32343830|3e6360603f03637f|3e6363633f03633e|0c0c0c183060637f|3e6363633e63633e|3e63607e6363633e
FontBitmap DIGITS_1[] = {
        0x3e6363636363633e,
        0x7e181818181a1c18,
        0x7f6306083060633e,
        0x3e6360603860633e,
        0x7830307f32343830,
        0x3e6360603f03637f,
        0x3e6363633f03633e,
        0x0c0c0c183060637f,
        0x3e6363633e63633e,
        0x3e63607e6363633e
};

// https://xantorohara.github.io/led-matrix-editor/#3f3f333333333f3f|0303030303030303|3f3f033f3f303f3f|3f3f303e3e303f3f|3030303f3f333333|3f3f303f3f033f3f|3f3f333f3f033f3f|3030303030303f3f|3f3f333f3f333f3f|3f3f303f3f333f3f
FontBitmap DIGITS_2[] = {
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
*/

enum {
    DIGIT_0,
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4,
    DIGIT_5,
    DIGIT_6,
    DIGIT_7,
    DIGIT_8,
    DIGIT_9,
    MINUS,
    SETUP,
    BRIGHTNESS,
    HUE,
    SATURATION,
};

/*
https://xantorohara.github.io/led-matrix-editor/#000f09090909090f|0002020202020202|000f01010f08080f|000f08080e08080f|000808080f090909|000f08080f01010f|000f09090f01010f|000808080808080f|000f09090f09090f|000f08080f09090f|0000000003000000|0077557714140000
*/
FontBitmap FONT[] = {
        0x000f09090909090f,
        0x0002020202020202,
        0x000f01010f08080f,
        0x000f08080e08080f,
        0x000808080f090909,
        0x000f08080f01010f,
        0x000f09090f01010f,
        0x000808080808080f,
        0x000f09090f09090f,
        0x000f08080f09090f,
        0x0000000003000000,
        0x0010ff1002ff0200,
        0x185a3ce7e73c5a18,
        0x3c72f9e5e5f9723c,
        0x3c428199b9f1623c,
        0x0066b9d966462418,
        0x0077557714140000
};

// https://xantorohara.github.io/led-matrix-editor/#0037515252543700|00eea8a8aea2ee00|30383f3f3f3f3830|00333f1e1e3f3300|30383f3f3f3f3830|00001b0e0e1b0000|00383c3c3c3808f0|001c3c3c3c1c100f
FontBitmap SYMBOLS[]  = {
        0x181c1f1f1f1f1c18, // speaker
        0x0000090606090000, // x
        0x0037515252543700,  // zd
        0x00eea8a8aea2ee00,  // 50
        0x383c3c3c3808f0e0,
        0x1c3c3c3c1c100f07,
};

#endif //ZD50_DISPLAY_FONT_H
