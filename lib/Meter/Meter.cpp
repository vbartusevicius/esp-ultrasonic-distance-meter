#include "Meter.h"

Meter::Meter(Logger* logger)
{
    this->logger = logger;
    this->speedOfSound = 331.3 * sqrt(1 + (Meter::CURRENT_TEMP / Meter::ABSOLUTE_TEMP));

    pinMode(Meter::TRIG_PIN, OUTPUT);
    pinMode(Meter::ECHO_PIN, INPUT_PULLUP);
}

/*
 * returns the measured distance from the sensor to the column in meters
 */
float Meter::measure()
{
    digitalWrite(Meter::TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(Meter::TRIG_PIN, HIGH);
    delayMicroseconds(20);
    digitalWrite(Meter::TRIG_PIN, LOW);

    // time in seconds
    float timeTook = (float) pulseIn(Meter::ECHO_PIN, HIGH, 100000) / 1000000;
    float distance = this->speedOfSound * timeTook;

    this->logger->info("Measurement taken. time: " + String(timeTook) + "s, distance: " + String(distance) + "m.");

    return distance;
}
