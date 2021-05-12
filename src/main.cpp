#include "ZD50.h"

using namespace ace_routine;
#if defined(LED_BUILTIN) && (LED_BUILTIN != 0)
COROUTINE(heartbeat) {
    COROUTINE_LOOP() {
        digitalWrite(LED_BUILTIN, HIGH);
        COROUTINE_DELAY(100);
        digitalWrite(LED_BUILTIN, LOW);
        COROUTINE_DELAY(500);
    }
}
#endif

void setup(void) {
#if defined(LED_BUILTIN) && (LED_BUILTIN != 0)
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
#endif

    ZD50::init();
    CoroutineScheduler::setup();
}

void loop() {
    CoroutineScheduler::loop();
}
