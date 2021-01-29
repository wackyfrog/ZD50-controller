//
// Created by Oleksandr Degtiar on 21.10.2020.
//

#include <Luminance.h>

#include "Luminance.h"

/**
 *
 */
namespace Luminance {
    static int luminance = 0;

    int update() {
//        luminance = analogRead(LUMINANCE_PIN_SENSOR);
        return luminance;
    }

    int getValue() {
        return luminance;
    }

    void init() {

    }
}
