#include "Stats.h"
#include "TimeHelper.h"
#include <ESP8266WiFi.h>

Stats::Stats() {}

void Stats::updateStats(float distance)
{
    this->ipAddress = String(WiFi.localIP().toString());
    this->network = String(WiFi.SSID());
    this->wifiSignal = String(String(WiFi.RSSI()) + "dBm");

    char value[8];
    snprintf(value, sizeof(value), "%.0f%%", distance * 100);
    this->relativeDistance = String(value);

    char buffer[32];
    TimeHelper::getUptime(buffer);
    this->uptime = String(buffer);
}
