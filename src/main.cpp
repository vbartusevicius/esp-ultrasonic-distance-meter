#include <Arduino.h>
#include "Logger.h"

Logger* logger;

void setup()
{
    Serial.begin(9600);

    while (!Serial && !Serial.available()) {
    }
    logger = new Logger(&Serial, "System");
}

void loop()
{
    logger->info("Logger works!");
    delay(1000);
}
