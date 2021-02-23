#ifndef Display_h
#define Display_h

#define FLIPPED_MATRIX

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

    void init();

    void print(char *text);

    void clearBuffer();

    void setBrightness(uint8_t level); // level 0-16, 0 means display off

    void standby();

    void operate();

    void blink(Blink rate);

    void displayOn();

    void displayOff();

    void modeMute();

    void clear();

    void send(uint8_t val);

    uint8_t getRamAdr(uint8_t row);

    void print(const int volume);

    void printBitmap(const char x, const char y, const uint64_t *image);

    uint8_t getBitmapWidth(const uint64_t *image);

    void flushBuffer();

    void displayWelcome();

    void displayHeadphones();

    uint8_t getBrightness();

//    void setFont(Font newFont);

//    Font getFont();

};

#endif
