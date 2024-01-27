#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>

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
Stats stats;

float measuredDistance = 0.0;
float relativeDistance = 0.0;
float absoluteDistance = 0.0;

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
    led = new LedController();
    mqtt = new MqttClient(storage, logger);
    admin = new WebAdmin(storage, logger, &resetCallback);
    meter = new Meter(logger);
    calculator = new DistanceCalculator(storage);

    wifi->begin();
    storage->begin();
    admin->begin();
    mqtt->begin();

    taskManager.schedule(repeatSeconds(1), [] { led->run(); });
    taskManager.schedule(repeatSeconds(1), [] { admin->run(&stats); });
    taskManager.schedule(repeatMillis(500), [] { mqtt->run(); });
    taskManager.schedule(repeatMillis(500), [] { wifi->run(); });
    taskManager.schedule(repeatSeconds(1), [] { stats.updateStats(relativeDistance); });

    // taskManager.schedule(repeatSeconds(10), [] {
    //     measuredDistance = meter->measure();
    //     relativeDistance = calculator->getRelative(measuredDistance);
    //     absoluteDistance = calculator->getAbsolute(measuredDistance);
    // });
    taskManager.schedule(repeatSeconds(1), [] {
        measuredDistance = (float) random(10, 110) / 100;
        relativeDistance = calculator->getRelative(measuredDistance);
        absoluteDistance = calculator->getAbsolute(measuredDistance);
    });
    taskManager.schedule(repeatSeconds(1), [] {
        mqtt->sendDistance(relativeDistance, absoluteDistance);
        display.setProgress(relativeDistance);
        
        display.run();
    });
}

void loop()
{
    taskManager.runLoop();
}
