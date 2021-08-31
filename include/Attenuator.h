//
// Created by Oleksandr Degtiar on 21.10.2020.
//

#ifndef ZD50_ATTENUATOR
#define ZD50_ATTENUATOR

#include <Arduino.h>


#include "Config.h"

// level 0 - 63
#define ATTENUATOR_STEPS ( 6 )
#define ATTENUATOR_STEP_DB ( 1.5 )

#define ATTENUATOR_LEVEL_MASK ( 0b00111111 )
#define ATT_RELAY_PULSE_MS ( 5 )

#define MAX_ATTENUATION_LEVEL ATTENUATOR_LEVEL_MASK
#define MIN_ATTENUATION_LEVEL ( 0 )

#define VOLUME_TO_ATTENUATION_LEVEL(volume) (volume > 0 ? MAX_ATTENUATION_LEVEL - volume + 1: MAX_ATTENUATION_LEVEL)
#define VOLUME_TO_MUTE_STATE(volume) (volume == 0)
#define ATTENUATION_LEVEL_TO_DB(level) (ATTENUATOR_STEP_DB * level)

namespace Attenuator {

    typedef enum {
        POWER_SAVE, // Powering not more than one relay per channel at once.
        NORMAL // Powering all necessary relays at same time.
    } SendMode;

    void init();

    /**
     * Set attenuation level and don't change mute state, transmit data into device.
     * @param attenuation
     */
    void setLevel(const uint8_t attenuation);

    /**
     * Set attenuation level and mute state, transmit data into device.
     * @param attenuation
     * @param isMuted
     */
    void setLevel(uint8_t attenuation, bool isMuted);

    /**
     * Get current attenuation level.
     * @return attenuation level
     */
    uint8_t getLevel();

    /**
     * Get mute state.
     * @return
     */
    bool isMuted();

    /**
     * Mute.
     */
    void mute();

    /**
     * Unmute.
     */
    void unmute();


    /**
     * @return
     */
    SendMode getMode();

    void setMode(SendMode sendMode);
};


#endif //ZD50_ATTENUATOR
