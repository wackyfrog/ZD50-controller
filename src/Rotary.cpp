
#include "Rotary.h"
#include "ZD50.h"

namespace Rotary {
    using namespace ZD50;
/*
 * Used Arduino RotaryEncoder library by Ben Buxton
 * The below state table has, for each state (row), the new state
 * to set based on the next encoder output. From left to right in,
 * the table, the encoder outputs are 00, 01, 10, 11, and the value
 * in that position is the new state to set.
 */

#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Counter-clockwise step.
#define DIR_CCW 0x20

#define R_START 0x0

#ifdef HALF_STEP
    // Use the half-step state table (emits a code at 00 and 11)
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
const unsigned char ttable[6][4] = {
  // R_START (00)
  {R_START_M,            R_CW_BEGIN,     R_CCW_BEGIN,  R_START},
  // R_CCW_BEGIN
  {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START},
  // R_CW_BEGIN
  {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START},
  // R_START_M (11)
  {R_START_M,            R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},
  // R_CW_BEGIN_M
  {R_START_M,            R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},
  // R_CCW_BEGIN_M
  {R_START_M,            R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW},
};
#else
// Use the full-step state table (emits a code at 00 only)
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

    const unsigned char rotaryStates[7][4] = {
            // R_START
            {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
            // R_CW_FINAL
            {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
            // R_CW_BEGIN
            {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
            // R_CW_NEXT
            {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
            // R_CCW_BEGIN
            {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
            // R_CCW_FINAL
            {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
            // R_CCW_NEXT
            {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
    };
#endif

    static State state = R_START;

    volatile static Value pendingValue = 0;

    volatile static bool isValueChanged = false;

    void ISR_rotation(void) {
        unsigned char pinstate =
                ((ROTARY_PORTIN & ROTARY_PIN_B_BIT) ? 0b10 : 0b00) | (ROTARY_PORTIN & ROTARY_PIN_A_BIT ? 0b01 : 0b00);
        state = rotaryStates[state & 0xf][pinstate];

        switch (state & 0x30) {
            case DIR_CW:
                pendingValue++;
                isValueChanged = true;
                break;

            case DIR_CCW:
                pendingValue--;
                isValueChanged = true;
                break;

            default:
                break;
        }
    }

    COROUTINE(rotaryReader) {
        COROUTINE_LOOP() {
            static int8_t value = 0;
            COROUTINE_AWAIT(isValueChanged);
            cli();
            value = pendingValue;
            pendingValue = 0;
            isValueChanged = false;
            sei();

            if (value != 0) {
                ZD50::command(Controller::Command::ROTATE, value);
                COROUTINE_DELAY(10);
            }
        }
    }

    void init() {
        ROTARY_DDR &= ~(ROTARY_PIN_A_BIT | ROTARY_PIN_B_BIT);
        ROTARY_PORT |= ROTARY_PIN_A_BIT | ROTARY_PIN_B_BIT;

        attachInterrupt(0, ISR_rotation, CHANGE);
        attachInterrupt(1, ISR_rotation, CHANGE);
    }


}
