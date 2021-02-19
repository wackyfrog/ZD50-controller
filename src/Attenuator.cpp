//
// Created by Oleksandr Degtiar on 21.10.2020.
//

#include "Attenuator.h"
#include <util/delay.h>
#include "ZD50.h"
#include <AceCommon.h>

namespace Attenuator {
    using namespace ZD50;

    typedef enum {
        OFF,
        SET_AND_RESET,
        SET_AND_OFF,
        OFF_AND_RESET
    } RelayState;

    static SendMode mode = POWER_SAVE;

/**
 * Current attenuation level
 */
    static uint8_t _level;

/**
 * State of mute
 */
    bool _isMuted;

/**
 * Send value of attenuation and mute state into attenuator's data register
 * @param attenuation
 * @param isMuted
 */
    void send();

/**
  * Sends 16 bit data into attenuator register via SPI bus.
  *
  * @param setLevelBits
  * @param mute
  * @param useState
  */
    void _send(const uint8_t setLevelBits, const uint8_t clearLevelBits, const bool mute);

    void init() {
        ATTENUATOR_IO_INIT();
        ATTENUATOR_IO_ALL_LO();
    }

    bool isMuted() {
        return _isMuted;
    }

    void mute() {
        if (isMuted()) {
            return;
        }
        _isMuted = true;
        send();
    }

    void unmute() {
        if (!isMuted()) {
            return;
        }
        _isMuted = false;
        send();
    }

    uint8_t getLevel() {
        return _level;
    }

    void setLevel(const uint8_t newLevel) {
        _level = newLevel & ATTENUATOR_LEVEL_MASK;
        send();
    }

    void setLevel(const uint8_t newLevel, const bool isMuted) {
        _level = newLevel & ATTENUATOR_LEVEL_MASK;
        SerialOut.print(F("========================"));
        SerialOut.print(F("SET_ATTENUATION_LEVEL: "));
        SerialOut.println(_level);
        SerialOut.println();
        _isMuted = isMuted;
        send();
    }

    void sendInPowerSaveMode() {
        uint8_t lastSentLevel;
        uint8_t maskedLevel;
        char bitCounter;

        lastSentLevel = 0xFF;
//        ZD50::Serial.println(F("SET_AND_OFF"));
        for (bitCounter = 5; bitCounter >= 0; bitCounter--) {
//            maskedLevel = _level & (1 << bitCounter);
            _send(_level & (1 << bitCounter), ~_level & (1 << bitCounter), _isMuted);
//            lastSentLevel = maskedLevel;
            _delay_ms(ATT_RELAY_PULSE_MS);
        }

        SerialOut.println();
    }

    void _serialOutBinary(uint16_t relayRegister);

#define RELAY_STEP_PASS 0b10
#define RELAY_STEP_ATTENUATE 0b01
#define RELAY_STEP_OFF 0b00

    void _send(const uint8_t setLevelBits, const uint8_t clearLevelBits, const bool mute) {
        uint16_t relayRegister = 0;
        char bitCounter;
        SerialOut.print(F(" lv "));
        SerialOut.println(setLevelBits);

        // set two bits for each attenuation value bit from 6 to 1
        for (bitCounter = 5; bitCounter >= 0; bitCounter--) {
            relayRegister <<= 2;
            relayRegister |= (setLevelBits & (1 << bitCounter)) ? RELAY_STEP_PASS : RELAY_STEP_OFF;
            relayRegister |= (clearLevelBits & (1 << bitCounter)) ? RELAY_STEP_ATTENUATE : RELAY_STEP_OFF;
        }

        // shift bits corresponding to hardware wiring
        relayRegister =
                ((relayRegister & 0xFC0) << 3) // 5-3 bits of level to 9-14 bits of shift register
                |
                ((relayRegister & 0x3F) << 1); // 0-2 bits of level to 1-7 bits of shift register
        if (!_isMuted) {
            // bit 8 of shift register is mute state (actite low): 0 - mute is on, 1 - mute is off
            relayRegister |= (1 << 8);
        }
        SerialOut.print(F(" rg "));
        _serialOutBinary(relayRegister);
        SerialOut.println();

        for (bitCounter = 0; bitCounter <= 15; bitCounter++) {
            if (relayRegister & (1 << 15)) {
                ATTENUATOR_IO_DO_HI();
            } else {
                ATTENUATOR_IO_DO_LO();
            }

            ATTENUATOR_IO_CLK_HI();
            relayRegister = relayRegister << 1;
            ATTENUATOR_IO_CLK_LO();
        }
        ATTENUATOR_IO_CS_HI();
        ATTENUATOR_IO_ALL_LO();
    }

    void _serialOutBinary(uint16_t relayRegister) {
        for (int i = 15; i >= 0; i--) {
            SerialOut.print((relayRegister & (1 << i)) ? 1 : 0);
            if (i == 8) {
                SerialOut.print(F(" "));
            }
        }
    }

    void send() {
        switch (mode) {
            case NORMAL:
                _send(_level, 0, _isMuted);
                _send(_level, ~_level, _isMuted);
                _delay_ms(ATT_RELAY_PULSE_MS);
                _send(0, 0, _isMuted);
                break;

            case POWER_SAVE:
                sendInPowerSaveMode();
                _send(0, 0, _isMuted);
                break;

        }

    }

    SendMode getMode() {
        return mode;
    }

    void setMode(SendMode sendMode) {
        mode = sendMode;
    }

}
