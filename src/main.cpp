#include "ZD50.h"

using namespace ace_routine;

COROUTINE(heartbeat) {
    COROUTINE_LOOP() {
        LED_ON();
        COROUTINE_DELAY(50);
        LED_OFF();
        COROUTINE_DELAY(1000);
    }
}

#if 0
COROUTINE(serialPing) {
    static uint32_t t = 0;
    COROUTINE_LOOP() {
        SerialOut.print(F("... ping "));
        SerialOut.println(++t, (uint8_t) 10);
        COROUTINE_DELAY_SECONDS(2);
    }
}
#endif

void setup(void) {
    LED_ENABLE();
    LED_ON();
    ZD50::init();
    CoroutineScheduler::setup();
}

void loop() {
    CoroutineScheduler::loop();
}
