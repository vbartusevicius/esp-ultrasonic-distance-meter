#include <Arduino.h>
#include "Logger.h"
#include "WifiConnector.h"
#include "LedController.h"

Logger* logger;
WifiConnector* wifi;
LedController* led;

void setup()
{
    Serial.begin(9600);

    while (!Serial && !Serial.available()) {
    }

    logger = new Logger(&Serial, "System");
    wifi = new WifiConnector(logger);
    led = new LedController(1000);

    wifi->connect();
}

void loop()
{
    wifi->process();
    led->process();

    logger->info("IP address: " + wifi->getIp());

    delay(100);
}
