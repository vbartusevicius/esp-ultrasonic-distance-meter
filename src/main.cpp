#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Logger.h"
#include "WifiConnector.h"
#include "LedController.h"
#include "WebAdmin.h"
#include "Storage.h"
#include "MqttClient.h"
#include "Meter.h"
#include "DistanceCalculator.h"
#include "Display.h"

WiFiClient network;
Display display;

float relativeDistance = 0;
float absoluteDistance = 0;
unsigned int lastUpdate = 0;
unsigned int updateInterval = 1000;

Logger* logger;
WifiConnector* wifi;
LedController* led;
WebAdmin* admin;
Storage* storage;
MqttClient* mqtt;
Meter* meter;
DistanceCalculator* calculator;

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
    meter = new Meter(logger);
    calculator = new DistanceCalculator(storage);

    wifi->begin();
    storage->begin();
    admin->begin();
    mqtt->begin();
}

float roundToTwo(float number)
{
    float value = (int)(number * 100 + .5);
    return (float)value / 100;
}

void loop()
{
    wifi->run();
    led->run();
    admin->run();
    mqtt->run();

    auto now = millis();
    if (now - lastUpdate < updateInterval) {
        return;
    }

    lastUpdate = now;
    // float distance = meter->measure();
    float distance = (float) random(10, 110) / 100;

    relativeDistance = calculator->getRelative(distance);
    absoluteDistance = calculator->getAbsolute(distance);
 
    mqtt->sendDistance(relativeDistance, absoluteDistance);
    display.setProgress(relativeDistance);
    
    display.run();
}
