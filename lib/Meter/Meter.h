#ifndef METER_H
#define METER_H

#include <Arduino.h>
#include "Logger.h"

class Meter
{
    private:
        static constexpr int TRIG_PIN = 14;
        static constexpr int ECHO_PIN = 12;
        static constexpr float ABSOLUTE_TEMP = 273.16;
        static constexpr float CURRENT_TEMP = 15.0;

        float speedOfSound;
        Logger* logger;

    public:
        Meter(Logger* logger);
        float measure();
};

#endif