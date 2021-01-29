#include <avr/pgmspace.h>
#include <string.h>
#include "Display.h"
#include "ZD50.h"
#include "Display/Font.h"
#include <SoftI2C.h>
#include "Config.h"
//Commands
#define HT16K33_DDAP          0b00000000 // Display data address pointer: 0000xxxx
#define HT16K33_SS            0b00100000 // System setup register
#define HT16K33_SS_STANDBY    0b00000000 // System setup - oscillator in standby mode
#define HT16K33_SS_NORMAL     0b00000001 // System setup - oscillator in normal mode
#define HT16K33_KDAP          0b01000000 // Key Address Data Pointer
#define HT16K33_IFAP          0b01100000 // Read status of INT flag
#define HT16K33_DSP           0b10000000 // Display setup
#define HT16K33_DSP_OFF       0b00000000 // Display setup - display off
#define HT16K33_DSP_ON        0b00000001 // Display setup - display on
#define HT16K33_DSP_NOBLINK   0b00000000 // Display setup - no blink
#define HT16K33_DSP_BLINK2HZ  0b00000010 // Display setup - 2hz blink
#define HT16K33_DSP_BLINK1HZ  0b00000100 // Display setup - 1hz blink
#define HT16K33_DSP_BLINK05HZ 0b00000110 // Display setup - 0.5hz blink
#define HT16K33_RIS           0b10100000 // ROW/INT Set
#define HT16K33_RIS_OUT       0b00000000 // Set INT as row driver output
#define HT16K33_RIS_INTL      0b00000001 // Set INT as int active low
#define HT16K33_RIS_INTH      0b00000011 // Set INT as int active high
#define HT16K33_DIM           0b11100000 // Dimming set
#define HT16K33_DIM_1         0b00000000 // Dimming set - 1/16
#define HT16K33_DIM_2         0b00000001 // Dimming set - 2/16
#define HT16K33_DIM_3         0b00000010 // Dimming set - 3/16
#define HT16K33_DIM_4         0b00000011 // Dimming set - 4/16
#define HT16K33_DIM_5         0b00000100 // Dimming set - 5/16
#define HT16K33_DIM_6         0b00000101 // Dimming set - 6/16
#define HT16K33_DIM_7         0b00000110 // Dimming set - 7/16
#define HT16K33_DIM_8         0b00000111 // Dimming set - 8/16
#define HT16K33_DIM_9         0b00001000 // Dimming set - 9/16
#define HT16K33_DIM_10        0b00001001 // Dimming set - 10/16
#define HT16K33_DIM_11        0b00001010 // Dimming set - 11/16
#define HT16K33_DIM_12        0b00001011 // Dimming set - 12/16
#define HT16K33_DIM_13        0b00001100 // Dimming set - 13/16
#define HT16K33_DIM_14        0b00001101 // Dimming set - 14/16
#define HT16K33_DIM_15        0b00001110 // Dimming set - 15/16
#define HT16K33_DIM_16        0b000001111 // Dimming set - 16/16

#define I2C_READ 1
#define I2C_WRITE 0

#define ROW_RAM_ADDR(row) (row < 8 ? row << 1 : ((row - 8) << 1) | 0x01)

namespace Display {

    static uint8_t address = 0x70;

    static Font font = FONT_1;

    uint8_t buffer[16];

//    SoftI2C i2c(DISPLAY_I2C_PIN_SDA, DISPLAY_I2C_PIN_SCL, &DISPLAY_I2C_DDR, &DISPLAY_I2C_PIN, &DISPLAY_I2C_PORT, true);

    void clearBuffer() {
        memset(buffer, 0, sizeof(buffer));
    }

    void print(char *text) {

    }

    void setFont(Font newFont) {
        font = newFont;
    }

    Font getFont() {
        return font;
    }


    void send(uint8_t val) {
        i2c_start();
        i2c_writebyte((address << 1) | I2C_WRITE);
        i2c_writebyte(val);
        i2c_stop();
    }


    void setBrightness(uint8_t level) {
        if (HT16K33_DIM_1 >= 0 && level < HT16K33_DIM_16) {
            send(HT16K33_DIM | level);
        }
    }

    void standby() {
        send(HT16K33_SS | HT16K33_SS_STANDBY);
    }

    void operate() {
        send(HT16K33_SS | HT16K33_SS_NORMAL);
    }

    void blink(Blink rate) {
        switch (rate) {
            case NONE:
                send(HT16K33_DSP | HT16K33_DSP_NOBLINK | HT16K33_DSP_ON);
                break;
            case SLOW:
                send(HT16K33_DSP | HT16K33_DSP_BLINK05HZ | HT16K33_DSP_ON);
                break;
            case MEDIUM:
                send(HT16K33_DSP | HT16K33_DSP_BLINK1HZ | HT16K33_DSP_ON);
                break;
            case FAST:
                send(HT16K33_DSP | HT16K33_DSP_BLINK2HZ | HT16K33_DSP_ON);
                break;
        }
    }

    void displayOn() {
        send(HT16K33_DSP | HT16K33_DSP_ON);
    }

    void displayOff() {
        send(HT16K33_DSP | HT16K33_DSP_OFF);
    }


/**
 * Flip a bitboard about the antidiagonal a8-h1.
 * Square a1 is mapped to h8 and vice versa.
 * @param x any bitboard
 * @return bitboard x flipped about antidiagonal a8-h1
 * @url https://www.chessprogramming.org/Flipping_Mirroring_and_Rotating
 */
    uint64_t flipDiagA8H1(uint64_t x) {
        uint64_t t;
        const uint64_t k1 = (0xaa00aa00aa00aa00);
        const uint64_t k2 = (0xcccc0000cccc0000);
        const uint64_t k4 = (0xf0f0f0f00f0f0f0f);
        t = x ^ (x << 36);
        x ^= k4 & (t ^ (x >> 36));
        t = k2 & (x ^ (x << 18));
        x ^= t ^ (t >> 18);
        t = k1 & (x ^ (x << 9));
        x ^= t ^ (t >> 9);
        return x;
    }

/**
 * Flip a bitboard about the diagonal a1-h8.
 * Square h1 is mapped to a8 and vice versa.
 * @param x any bitboard
 * @return bitboard x flipped about diagonal a1-h8
 * @url https://www.chessprogramming.org/Flipping_Mirroring_and_Rotating
 */
    uint64_t flipDiagA1H8(uint64_t x) {
        uint64_t t;
        const uint64_t k1 = 0x5500550055005500;
        const uint64_t k2 = 0x3333000033330000;
        const uint64_t k4 = 0x0f0f0f0f00000000;
        t = k4 & (x ^ (x << 28));
        x ^= t ^ (t >> 28);
        t = k2 & (x ^ (x << 14));
        x ^= t ^ (t >> 14);
        t = k1 & (x ^ (x << 7));
        x ^= t ^ (t >> 7);
        return x;
    }

/**
 * Flip a bitboard vertically about the centre ranks.
 * Rank 1 is mapped to rank 8 and vice versa.
 * @param x any bitboard
 * @return bitboard x flipped vertically
 * @url https://www.chessprogramming.org/Flipping_Mirroring_and_Rotating
 */
    uint64_t flipVertical(uint64_t x) {
        const uint64_t k1 = uint64_t(0x00FF00FF00FF00FF);
        const uint64_t k2 = uint64_t(0x0000FFFF0000FFFF);
        x = ((x >> 8) & k1) | ((x & k1) << 8);
        x = ((x >> 16) & k2) | ((x & k2) << 16);
        x = (x >> 32) | (x << 32);
        return x;
    }

    uint8_t getRamAdr(uint8_t row) {
        return row < 8 ? row << 1 : ((row - 8) << 1) | 0x01;
    }

    void displayImage(const uint8_t x, const uint8_t y, const uint64_t *image) {
        uint8_t row;
        uint64_t bitmap;
        memcpy_P(&bitmap, (uint64_t *) image, 8);

#ifdef FLIPPED_MATRIX
        bitmap = flipVertical(flipDiagA8H1(bitmap));
        for (uint8_t i = 0; i < 8; i++) {
            row = x + i;
            if (row >= 0 && row <= 15) {
                buffer[ROW_RAM_ADDR(row)] = bitmap & 0xFF;
            }
            bitmap = bitmap >> 8;
        }
#else
        bitmap = flipDiagA1H8(bitmap);
        for (uint8_t i = 0; i < 8; i++) {
            row = 15 - x - i;
            if (row >= 0 && row <= 15) {
                buffer[ROW_RAM_ADDR(row)] = bitmap & 0xFF;
            }
            bitmap = bitmap >> 8;
        }
#endif
    }

    void flushBuffer() {
        i2c_start();
        i2c_writebyte((address << 1) | I2C_WRITE);

        i2c_writebyte(HT16K33_DDAP);
        for (unsigned int index = 0; index < sizeof(buffer); ++index) {
            i2c_writebyte(buffer[index]);
        }
        i2c_stop();
    }

    void printVolume(const uint8_t volume) {
        clearBuffer();

        if (font == FONT_2) {
            if (volume < 10) {
                displayImage(8 - (DIGITS_2_WIDTH[volume] >> 1), 0, (uint64_t *) &DIGITS_2[volume]);

            } else {
                uint8_t ed = volume % 10;
                uint8_t des = volume / 10;
                char xPos = (16 - DIGITS_2_WIDTH[ed] - DIGITS_2_WIDTH[des] - 2) / 2;

                ZD50::Serial.print(F("DISPL:xPos:"));
                ZD50::Serial.println(xPos);

                displayImage(xPos, 0, (uint64_t *) &DIGITS_2[des]);
                xPos += DIGITS_2_WIDTH[des] + 2;
                displayImage(xPos, 0, (uint64_t *) &DIGITS_2[ed]);
            }
        }

        if (font == FONT_1) {
            if (volume < 10) {
                displayImage(4, 0, (uint64_t *) &DIGITS_1[volume]);

            } else {
                displayImage(1, 0, (uint64_t *) &DIGITS_1[volume / 10]);
                displayImage(8, 0, (uint64_t *) &DIGITS_1[volume % 10]);
            }
        }


        flushBuffer();
    }

    void modeMute() {
        clearBuffer();
        displayImage(3, 0, (uint64_t *) &SYMBOLS[0]);
        displayImage(9, 0, (uint64_t *) &SYMBOLS[1]);
        flushBuffer();
        blink(FAST);
    }

    void displayWelcome() {
        clearBuffer();
        displayImage(0, 0, (uint64_t *) &SYMBOLS[2]);
        displayImage(8, 0, (uint64_t *) &SYMBOLS[3]);
        flushBuffer();
    }

    void displayHeadphones() {
        clearBuffer();
        displayImage(0, 0, (uint64_t *) &SYMBOLS[4]);
        displayImage(8, 0, (uint64_t *) &SYMBOLS[5]);
        flushBuffer();
    }

    void init() {
        i2c_init();
        send(HT16K33_SS | HT16K33_SS_NORMAL);
        send(HT16K33_RIS | HT16K33_RIS_OUT);
        setBrightness(0);
        displayOn();
    }

    void clear() {
        clearBuffer();
        flushBuffer();
    }


}
