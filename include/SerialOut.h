/*
 *  Based on library ATtinySerialOut by Armin Joachimsmeyer
 *  Email: armin.joachimsmeyer@gmail.com
 */

#ifndef SERIAL_OUT_H
#define SERIAL_OUT_H

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stdio.h>
#include "Config.h"

#if (F_CPU != 1000000) && (F_CPU != 8000000) && (F_CPU != 16000000)
#error F_CPU value must be 1000000, 8000000 or 16000000.
#endif

// FIXME It's seems 38400 is broken

#if (SERIAL_OUT_BAUD == SERIAL_OUT_BAUD_230400)
#if (F_CPU != 8000000) && (F_CPU != 16000000)
#error F_CPU value must be 8000000 or 16000000 for baudrate 230400
#endif
#elif (SERIAL_OUT_BAUD == SERIAL_OUT_BAUD_115200)
#elif (SERIAL_OUT_BAUD == SERIAL_OUT_BAUD_38400)
#else
#error Must define SERIAL_OUT_BAUD_230400, 115200 or 38400
#endif


/*
 * Define or comment this out, if you want to save 10 bytes code size and if you can live
 * with 87 micro seconds intervals of disabled interrupts for each sent byte @115200 baud.
 */
#define USE_ALWAYS_CLI_SEI_GUARD_FOR_OUTPUT

/*
 * @1 MHz use bigger (+120 bytes for unrolled loop) but faster code. Otherwise only 38400 baud is possible.
 * @8/16 MHz use 115200 baud instead of 230400 baud.
 */



extern bool sUseCliSeiForWrite; // default is true

void useCliSeiForStrings(
        bool aUseCliSeiForWrite); // might be useful to set to false if output is done from ISR, to avoid to call unwanted sei().

void initTXPin();

void write1Start8Data1StopNoParity(uint8_t aValue);

void write1Start8Data1StopNoParityWithCliSei(uint8_t aValue);

void writeValue(uint8_t aValue);

void writeString(const char *aStringPtr);

void writeString(const __FlashStringHelper *aStringPtr);

void writeString_P(const char *aStringPtr);

void writeString_E(const char *aStringPtr);

void writeStringWithCliSei(const char *aStringPtr);

void writeStringWithoutCliSei(const char *aStringPtr);

void writeStringSkipLeadingSpaces(const char *aStringPtr);

void writeBinary(uint8_t aByte); // write direct without decoding
void writeChar(uint8_t aChar); // Synonym for writeBinary
void writeCRLF();

void writeByte(int8_t aByte);

void writeUnsignedByte(uint8_t aByte);

void writeUnsignedByteHex(uint8_t aByte);

void writeUnsignedByteHexWithPrefix(uint8_t aByte);

void writeInt(int16_t aInteger);

void writeUnsignedInt(uint16_t aInteger);

void writeLong(int32_t aLong);

void writeUnsignedLong(uint32_t aLong);

void writeFloat(double aFloat);

void writeFloat(double aFloat, uint8_t aDigits);

char nibbleToHex(uint8_t aByte);

class TinySerialOut {
public:

    void begin(long);

    void end();

    void flush(void);

    void printHex(uint8_t aByte); // with 0x prefix
    void printHex(uint16_t aWord); // with 0x prefix
    void printlnHex(uint8_t aByte); // with 0x prefix
    void printlnHex(uint16_t aWord); // with 0x prefix

    // virtual functions of Print class
    size_t write(uint8_t aByte);

    operator bool(); // To support "while (!Serial); // wait for serial port to connect. Needed for Leonardo only

    void print(const __FlashStringHelper *aStringPtr);

    void print(const char *aStringPtr);

    void print(char aChar);

    void print(uint8_t aByte, uint8_t aBase = 10);

    void print(int16_t aInteger, uint8_t aBase = 10);

    void print(uint16_t aInteger, uint8_t aBase = 10);

    void print(int32_t aLong, uint8_t aBase = 10);

    void print(uint32_t aLong, uint8_t aBase = 10);

    void print(double aFloat, uint8_t aDigits = 2);

    void println(const char *aStringPtr);

    void println(const __FlashStringHelper *aStringPtr);

    void println(char aChar);

    void println(uint8_t aByte, uint8_t aBase = 10);

    void println(int16_t aInteger, uint8_t aBase = 10);

    void println(uint16_t aInteger, uint8_t aBase = 10);

    void println(int32_t aLong, uint8_t aBase = 10);

    void println(uint32_t aLong, uint8_t aBase = 10);

    void println(double aFloat, uint8_t aDigits = 2);

    void println(void);

};

#endif // SERIAL_OUT_H