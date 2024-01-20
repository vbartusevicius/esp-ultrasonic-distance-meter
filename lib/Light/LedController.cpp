#include "LedController.h"

LedController::LedController(unsigned int interval)
{
    this->interval = interval;
    this->lastTime = millis();
    this->lastState = false;

    pinMode(LED_BUILTIN, OUTPUT);
}

void LedController::run()
{
    auto time = millis();
    if ((time - this->lastTime) < this->interval) {
        return;
    }

    bool state = !this->lastState;
    digitalWrite(LED_BUILTIN, (int) state);

    this->lastTime = time;
    this->lastState = state;
}
