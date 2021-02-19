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

//    static Font font = FONT_1;

    uint8_t buffer[16];

    uint8_t brightness;

    void clearBuffer() {
        memset(buffer, 0, sizeof(buffer));
    }

//    void setFont(Font newFont) {
//        font = newFont;
//    }
//
//    Font getFont() {
//        return font;
//    }
//

    void send(uint8_t val) {
        i2c_start();
        i2c_writebyte((address << 1) | I2C_WRITE);
        i2c_writebyte(val);
        i2c_stop();
    }

    uint8_t getBrightness() {
        return brightness;
    }

    void setBrightness(uint8_t level) {
        brightness = level;
        if (level > HT16K33_DIM_16) {
            level = HT16K33_DIM_16;
        } else if (level < HT16K33_DIM_1) {
            level = HT16K33_DIM_1;
        }
        send(HT16K33_DIM | level);
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

    void printBitmap(const uint8_t x, const uint8_t y, const uint64_t *image) {
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

    uint8_t getBitmapWidth(const uint64_t *image) {
        uint64_t bitmap;
        uint64_t mask;
        uint8_t width;

        memcpy_P(&bitmap, (uint64_t *) image, 8);

        width = 8;
        mask = 0x8080808080808080;
        while ((width > 0) && ((bitmap & mask) == 0)) {
            width--;
            mask = mask >> 1;
        }
        return width;
    }

    void print(char *text) {
        uint8_t x = 0;
        char *textChar;
        textChar = text;
        // TODO Optimize
        uint8_t totalWidth = 0;

        while (*textChar != '\0') {
            uint64_t *bitmap = (uint64_t *) &FONT[(uint8_t) *textChar - 48];
            if (totalWidth > 0) {
                ++totalWidth;
            }
            totalWidth += getBitmapWidth(bitmap);
            textChar++;
        }

        textChar = text;
        x = totalWidth > 16 ? 0 : (16 - totalWidth) >> 1;
        while (*textChar != '\0') {
            uint64_t *bitmap = (uint64_t *) &FONT[(uint8_t) *textChar - 48];
            printBitmap(x, 0, bitmap);
            textChar++;
            if (x > 0) {
                ++x;
            }
            x += getBitmapWidth(bitmap);
        }
    }

    void printVolume(const char volume) {
        clearBuffer();

        char buf[8] = {"\0"};
        if (volume < 0) {
            itoa(-volume, buf + 1, 10);
            buf[0] = (char) 58;
        } else {
            itoa(volume, buf, 10);
        }
//        buf[strlen(buf)] = (char) 59;
        print(buf);
        flushBuffer();
    }

    void modeMute() {
        clearBuffer();
        printBitmap(3, 0, (uint64_t *) &SYMBOLS[0]);
        printBitmap(9, 0, (uint64_t *) &SYMBOLS[1]);
        flushBuffer();
        blink(FAST);
    }

    void displayWelcome() {
        clearBuffer();
        printBitmap(0, 0, (uint64_t *) &SYMBOLS[2]);
        printBitmap(8, 0, (uint64_t *) &SYMBOLS[3]);
        flushBuffer();
    }

    void displayHeadphones() {
        clearBuffer();
        printBitmap(0, 0, (uint64_t *) &SYMBOLS[4]);
        printBitmap(8, 0, (uint64_t *) &SYMBOLS[5]);
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
