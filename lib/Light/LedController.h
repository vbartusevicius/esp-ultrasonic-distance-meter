#include <Arduino.h>

class LedController
{
    private:
        unsigned int interval;
        unsigned long lastTime;
        bool lastState;

    public:
        LedController(unsigned int interval);
        void process();
};
