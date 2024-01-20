#include "WifiConnector.h"

WifiConnector::WifiConnector(Logger* logger)
{
    this->logger = logger;

    WiFi.mode(WIFI_STA);

    this->wm = new WiFiManager();
    this->wm->resetSettings();
}

bool WifiConnector::process()
{
    bool connected = this->wm->process();

    if (!connected) {
        this->logger->info("WiFi connection lost");
    }

    return connected;
}

bool WifiConnector::connect()
{
    this->wm->setConfigPortalBlocking(false);
    this->wm->setConfigPortalTimeout(300);

    bool connected = this->wm->autoConnect(
        ("ESP_distance_meter_" + String(ESP.getChipId())).c_str()
    );

    if (connected) {
        this->logger->info("Connected to WiFi");
    } else {
        this->logger->info("Serving WiFi configuration portal");
    }

    return connected;
}
