#include <Arduino.h>
#include "Logger.h"
#include "WifiConnector.h"

Logger* logger;
WifiConnector* wifi;

void setup()
{
    Serial.begin(9600);

    while (!Serial && !Serial.available()) {
    }

    logger = new Logger(&Serial, "System");
    wifi = new WifiConnector(logger);

    wifi->connect();
}

void loop()
{
    wifi->process();
    logger->info("IP address: " + wifi->getIp());

    delay(1000);
}
