#include "WifiConnector.h"

WifiConnector::WifiConnector(Logger* logger)
{
    this->logger = logger;
    this->appName = "ESP_distance_meter";

    WiFi.mode(WIFI_STA);
    WiFi.setHostname(this->appName);
}

void WifiConnector::run()
{
    wm.process();
}

bool WifiConnector::begin()
{
    wm.setConfigPortalBlocking(false);
    wm.setConfigPortalTimeout(300);

    bool connected = wm.autoConnect(this->appName);

    if (connected) {
        this->logger->info("Connected to WiFi.");
    } else {
        this->logger->info("Serving WiFi configuration portal.");
    }

    return connected;
}

void WifiConnector::resetSettings()
{
    wm.resetSettings();
}
