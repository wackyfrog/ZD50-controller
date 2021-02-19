//
// Created by Oleksandr Degtiar on 21.10.2020.
//

#include <Luminance.h>

#include "Luminance.h"
#include <Arduino.h>

/**
 *
 */
namespace Luminance {
    static int luminance = 0;

    int read() {
        luminance = analogRead(LUMINANCE_PIN_SENSOR);
        return luminance;
    }

    int getValue() {
        return luminance;
    }

    void init() {
        pinMode(LUMINANCE_PIN_SENSOR, INPUT_PULLUP);
    }
}
