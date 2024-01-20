#include <Arduino.h>
#include "Logger.h"
#include "WifiConnector.h"
#include "LedController.h"
#include "WebAdmin.h"

Logger* logger;
WifiConnector* wifi;
LedController* led;
WebAdmin* admin;

void setup()
{
    Serial.begin(9600);

    while (!Serial && !Serial.available()) {
    }

    logger = new Logger(&Serial, "System");
    wifi = new WifiConnector(logger);
    led = new LedController(1000);
    admin = new WebAdmin();

    wifi->connect();

    admin->renderAdmin();
}

void loop()
{
    wifi->process();
    led->process();
    admin->updateAdmin();

    delay(100);
}
