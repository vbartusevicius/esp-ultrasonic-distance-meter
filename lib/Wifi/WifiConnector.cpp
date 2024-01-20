#include "WifiConnector.h"

WifiConnector::WifiConnector(Logger* logger)
{
    this->logger = logger;
    this->appName = "ESP_distance_meter";

    WiFi.mode(WIFI_STA);
    WiFi.setHostname(this->appName);

    this->wm = new WiFiManager();
}

void WifiConnector::process()
{
    this->wm->process();
}

String WifiConnector::getIp()
{
    return WiFi.localIP().toString();
}

bool WifiConnector::connect()
{
    this->wm->setConfigPortalBlocking(false);
    this->wm->setConfigPortalTimeout(300);

    bool connected = this->wm->autoConnect(this->appName);

    if (connected) {
        this->logger->info("Connected to WiFi");
    } else {
        this->logger->info("Serving WiFi configuration portal");
    }

    return connected;
}
