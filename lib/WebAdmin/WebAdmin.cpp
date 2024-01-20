#include "WebAdmin.h"

WebAdmin::WebAdmin()
{
    this->lastUpdated = millis();
    this->interval = 1000;
}

void WebAdmin::renderAdmin()
{
    ControlColor color = ControlColor::None;
    String labelStyle = "width: 100%; text-align: left; font-weight: 500;";

    ESPUI.addControl(ControlType::Separator, "Sensor settings");
    ESPUI.addControl(ControlType::Number, "Distance to sensor when \"empty\" (cm)", "100", color);
    ESPUI.addControl(ControlType::Number, "Distance to sensor when \"full\" (cm)", "10", color);

    ESPUI.addControl(ControlType::Separator, "MQTT settings");
    ESPUI.addControl(ControlType::Text, "Host", "Hostname", color);
    ESPUI.addControl(ControlType::Number, "Port", "1883", color);
    ESPUI.addControl(ControlType::Text, "Username", "Username", color);
    ESPUI.addControl(ControlType::Password, "Password", "Password", color);

    auto deviceName = ESPUI.addControl(ControlType::Text, "Device name", "esp_distance_meter", color, Control::noParent);
    auto distanceTopic = ESPUI.addControl(ControlType::Label, "Distance topic", "Distance topic: {device_name}/stat/distance", color, deviceName);
    ESPUI.setElementStyle(distanceTopic, labelStyle);

    auto percentageTopic = ESPUI.addControl(ControlType::Label, "Percentage topic", "Percentage topic: {device_name}/stat/percentage", color, deviceName);
    ESPUI.setElementStyle(percentageTopic, labelStyle);

    this->statsId = ESPUI.addControl(ControlType::Label, "Stats", "", color);
    ESPUI.setElementStyle(this->statsId, labelStyle);

    ESPUI.setPanelWide(deviceName, true);
    ESPUI.setPanelWide(this->statsId, true);

    ESPUI.begin("ESP distance meter");
}

void WebAdmin::updateAdmin()
{
    auto time = millis();
    if (time - this->lastUpdated < this->interval) {
        return;
    }
    this->lastUpdated = time;

    char buffer[512];
    sprintf(
        buffer,
        "Network: %s<br>IP address: %s<br>Signal: %d dBm",
        WiFi.SSID().c_str(),
        WiFi.localIP().toString().c_str(),
        WiFi.RSSI()
    );

    auto stats = ESPUI.getControl(this->statsId);
    stats->value = buffer;

    ESPUI.updateControl(stats);
}
