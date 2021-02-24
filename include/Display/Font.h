//
// Created by Oleksandr Degtiar on 29.10.2020.
//

#ifndef ZD50_DISPLAY_FONT_H
#define ZD50_DISPLAY_FONT_H

#include <avr/pgmspace.h>

typedef const uint64_t FontBitmap PROGMEM;

namespace Font {
    FontBitmap IMG_SETTINGS = {0x0010ff1002ff0200};
    FontBitmap IMG_BRIGHTNESS = {0x185a3ce7e73c5a18};
    FontBitmap IMG_SATURATION = {0x3c72f9e5e5f9723c};
    FontBitmap IMG_HUE = {0x3c428199b9f1623c};
    FontBitmap IMG_IR = {0x070f07aaa0984038};
}

/*
https://xantorohara.github.io/led-matrix-editor/#000f09090909090f|0002020202020202|000f01010f08080f|000f08080e08080f|000808080f090909|000f08080f01010f|000f09090f01010f|000808080808080f|000f09090f09090f|000f08080f09090f|0000000003000000|0010ff1002ff0200|185a3ce7e73c5a18|3c72f9e5e5f9723c|3c428199b9f1623c|0066b9d966462418|0077557714140000
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
FontBitmap SYMBOLS[] = {
        0x181c1f1f1f1f1c18, // speaker
        0x0000090606090000, // x
        0x0037515252543700,  // zd
        0x00eea8a8aea2ee00,  // 50
        0x383c3c3c3808f0e0,
        0x1c3c3c3c1c100f07,
};

#endif //ZD50_DISPLAY_FONT_H
