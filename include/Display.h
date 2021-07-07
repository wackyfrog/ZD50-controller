#ifndef Display_h
#define Display_h

#define FLIPPED_MATRIX

#include "Display/Font.h"

namespace Display {
//    enum Font {
//        FONT_1
//    };

    typedef enum {
        CENTER = -1
    } Align;

    typedef enum {
        NONE,
        SLOW,
        MEDIUM,
        FAST
    } Blink;

    typedef enum {
        STANDBY,
        WELCOME,
        MUTE,
        HEADPHONES,
        VOLUME
    } Mode;

    void init();

    void adjustBrightness();

    void print(char *text);

    void print(const int volume);

    void clearBuffer();

    void setBrightness(uint8_t level); // level 0-15

    uint8_t getBrightness();

    void standby();

    void operate();

    void blink(Blink rate);

    void displayOn();

    void displayOff();

    void clear();

    void send(uint8_t val);

    uint8_t getRamAdr(uint8_t row);

    void pixel(const uint8_t col, const uint8_t row, bool lighten);

    void col(const uint8_t col, uint8_t pixels);

    void printBitmap(const char x, const char y, const uint64_t *image);

    uint8_t getBitmapWidth(const uint64_t *image);

    void flushBuffer();


    void setMode(Mode mode);

//    void setFont(Font newFont);

//    Font getFont();

};

#endif
