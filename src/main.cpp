#include <Arduino.h>
#include "Logger.h"
#include "WifiConnector.h"
#include "LedController.h"
#include "WebAdmin.h"
#include "Storage.h"

Logger* logger;
WifiConnector* wifi;
LedController* led;
WebAdmin* admin;
Storage* storage;

void resetCallback() {
    Serial.print("RESET requested");
}

void setup()
{
    Serial.begin(9600);

    while (!Serial && !Serial.available()) {
    }

    logger = new Logger(&Serial, "System");
    storage = new Storage();
    wifi = new WifiConnector(logger);
    led = new LedController(1000);

    admin = new WebAdmin(storage, &resetCallback);

    wifi->begin();

    storage->begin();
    admin->begin();
}

void loop()
{
    wifi->run();
    led->run();
    admin->run();

    // logger->info("IP address: " + WiFi.localIP().toString());

    // delay(100);
}
