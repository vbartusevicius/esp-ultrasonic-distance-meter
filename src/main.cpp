#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Logger.h"
#include "WifiConnector.h"
#include "LedController.h"
#include "WebAdmin.h"
#include "Storage.h"
#include "MqttClient.h"

WiFiClient network;

Logger* logger;
WifiConnector* wifi;
LedController* led;
WebAdmin* admin;
Storage* storage;
MqttClient* mqtt;

void resetCallback() {
    wifi->resetSettings();
    storage->reset();
    ESP.eraseConfig();

    delay(2000);
    ESP.restart();
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
    mqtt = new MqttClient(storage, logger);
    admin = new WebAdmin(storage, logger, &resetCallback);

    wifi->begin();
    storage->begin();
    admin->begin();
    mqtt->begin();
}

void loop()
{
    wifi->run();
    led->run();
    admin->run();
    mqtt->run();

    mqtt->sendDistance(55.43, 93.0);

    delay(500);
}
