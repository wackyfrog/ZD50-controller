//
// Created by Oleksandr Degtiar on 05.01.2021.
//
#include "Backlight.h"
#include "Backlight/ws2812.h"
#include "ZD50.h"

static uint8_t leds[BACKLIGHT_BUF_SIZE];
#define OFFSET_R(r) (r+1)
#define OFFSET_G(g) (g)
#define OFFSET_B(b) (b+2)

namespace Backlight {

    void init() {
        DDRD |= BACKLIGHT_PIN_MASK;
        fill((cRGB) {0, 30, 0});
    }

    cRGB getPixel(uint8_t index) {
        cRGB px_value;

        if (index < BACKLIGHT_LED_COUNT) {

            uint16_t tmp;
            tmp = index * 3;

            px_value.r = leds[OFFSET_R(tmp)];
            px_value.g = leds[OFFSET_G(tmp)];
            px_value.b = leds[OFFSET_B(tmp)];
        }

        return px_value;
    }

    void fill(cRGB color) {
        for (uint8_t ledIndex = 0; ledIndex < BACKLIGHT_BUF_SIZE; ledIndex += 3) {
            leds[OFFSET_R(ledIndex)] = color.r;
            leds[OFFSET_G(ledIndex)] = color.g;
            leds[OFFSET_B(ledIndex)] = color.b;
        }

    }

    uint8_t setPixel(uint8_t index, cRGB color) {
        if (index < BACKLIGHT_LED_COUNT) {

            uint16_t tmp;
            tmp = index * 3;

            leds[OFFSET_R(tmp)] = color.r;
            leds[OFFSET_G(tmp)] = color.g;
            leds[OFFSET_B(tmp)] = color.b;
            return 0;
        }
        return 1;
    }

    uint8_t setSubpixel(uint16_t index, uint8_t offset, uint8_t px_value) {
        if (index < BACKLIGHT_LED_COUNT) {
            uint16_t tmp;
            tmp = index * 3;

            leds[tmp + offset] = px_value;
            return 0;
        }
        return 1;
    }

    void update() {
#ifdef __AVR_ATmega324PA__
        ws2812_send(leds, BACKLIGHT_BUF_SIZE, BACKLIGHT_PIN_MASK, &BACKLIGHT_PORT);
#else
#error Backlight hardware is not configured
#endif
    }

}
