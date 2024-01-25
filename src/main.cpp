#include <Arduino.h>
#include <ESP8266WiFi.h>
// #include <U8g2lib.h>
// #include <UiUiUi.h>

#include "Logger.h"
#include "WifiConnector.h"
#include "LedController.h"
#include "WebAdmin.h"
#include "Storage.h"
#include "MqttClient.h"
#include "Meter.h"
#include "DistanceCalculator.h"

WiFiClient network;

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

// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 12, 14);

// UITextLine textLine=UITextLine(u8g2_font_6x10_tf);
// UIDisplay displayManager=UIDisplay(&textLine);

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

    // u8g2.begin();

    // textLine.setText("Hello world");
    // displayManager.init(&u8g2);
    // displayManager.render(&u8g2); 
}

void loop()
{
    wifi->run();
    led->run();
    admin->run();
    mqtt->run();

    auto now = millis();
    if (now - lastUpdate < updateInterval) {
        delay(100);
        return;
    }

    lastUpdate = now;
    float distance = meter->measure();

    relativeDistance = calculator->getRelative(distance);
    absoluteDistance = calculator->getAbsolute(distance);
    // relativeDistance = 0.43;
    // absoluteDistance = 44.35;

    mqtt->sendDistance(relativeDistance, absoluteDistance);

    // textLine.setText("Iteration " + now);
    // displayManager.render(&u8g2); 
}
