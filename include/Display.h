#ifndef Display_h
#define Display_h

#define FLIPPED_MATRIX

namespace Display {
    enum Font {
        FONT_1, FONT_2
    };

    enum Blink {
        NONE,
        SLOW,
        MEDIUM,
        FAST
    };

    void init();

    void print(char *text);

    void clearBuffer();

    void setBrightness(uint8_t level); // level 0-16, 0 means display off

    void standby();

    void operate();

    void blink(Blink rate);

    void displayOn();

    void displayOff();

    void printVolume(const uint8_t volume);

    void modeMute();

    void clear();

    void send(uint8_t val);

    uint8_t getRamAdr(uint8_t row);

    void displayImage(const uint8_t x, const uint8_t y, const uint64_t *image);

    void flushBuffer();

    void displayWelcome();

    void displayHeadphones();

    void setFont(Font newFont);

    Font getFont();

};

#endif
