#include "WebAdmin.h"
#include "Parameter.h"

extern WebAdmin* admin;

WebAdmin::WebAdmin(Storage* storage, ResetCallback resetCallback)
{
    this->storage = storage;
    this->resetCallback = resetCallback;

    this->lastUpdated = millis();
    this->interval = 1000;
}

char* WebAdmin::SUBMIT = "submit";
char* WebAdmin::RESET = "reset";

void WebAdmin::begin()
{
    String labelStyle = "width: 100%; text-align: left; font-weight: 500;";

    ESPUI.addControl(ControlType::Separator, "Sensor settings");
    this->addControl(
        ControlType::Number, 
        "Distance to sensor when \"empty\" (cm)", 
        this->storage->getParameter(Parameter::DISTANCE_EMPTY, "100"),
        Control::noParent,
        Parameter::DISTANCE_EMPTY
    );
    this->addControl(
        ControlType::Number, 
        "Distance to sensor when \"full\" (cm)", 
        this->storage->getParameter(Parameter::DISTANCE_FULL, "10"),
        Control::noParent,
        Parameter::DISTANCE_FULL
    );

    ESPUI.addControl(ControlType::Separator, "MQTT settings");
    this->addControl(
        ControlType::Text, 
        "Host", 
        this->storage->getParameter(Parameter::MQTT_HOST, "mosquitto.lan"),
        Control::noParent,
        Parameter::MQTT_HOST
    );
    this->addControl(
        ControlType::Number, 
        "Port", 
        this->storage->getParameter(Parameter::MQTT_PORT, "1883"),
        Control::noParent,
        Parameter::MQTT_PORT
    );
    this->addControl(
        ControlType::Text, 
        "Username", 
        this->storage->getParameter(Parameter::MQTT_USER, "username"),
        Control::noParent,
        Parameter::MQTT_USER
    );
    this->addControl(
        ControlType::Password, 
        "Password", 
        this->storage->getParameter(Parameter::MQTT_PASS, "password"),
        Control::noParent,
        Parameter::MQTT_PASS
    );
    String deviceName = this->storage->getParameter(Parameter::MQTT_DEVICE, "esp_distance_meter");
    auto deviceNameId = this->addControl(
        ControlType::Text, 
        "Device name", 
        deviceName,
        Control::noParent,
        Parameter::MQTT_DEVICE
    );

    this->distanceTopicId = this->addControl(
        ControlType::Label, 
        "Distance topic", 
        this->getDistanceTopic(deviceName), 
        deviceNameId
    );
    ESPUI.setElementStyle(this->distanceTopicId, labelStyle);

    this->percentageTopicId = this->addControl(
        ControlType::Label, 
        "Percentage topic", 
        this->getPercentageTopic(deviceName),
        deviceNameId
    );
    ESPUI.setElementStyle(this->percentageTopicId, labelStyle);

    ESPUI.addControl(ControlType::Separator, "General");

    auto submitId = this->addControl(
        ControlType::Button,
        "Actions",
        "Save & restart",
        Control::noParent,
        WebAdmin::SUBMIT
    );
    this->addControl(
        ControlType::Button,
        "Reset device",
        "Reset device",
        submitId,
        WebAdmin::RESET
    );
    ESPUI.getControl(submitId)->color = ControlColor::Carrot;

    this->statsId = this->addControl(
        ControlType::Label, 
        "Stats", 
        "", 
        Control::noParent
    );

    ESPUI.setElementStyle(this->statsId, labelStyle);

    ESPUI.setPanelWide(deviceNameId, true);
    ESPUI.setPanelWide(this->statsId, true);
    ESPUI.setPanelWide(submitId, true);

    ESPUI.begin("ESP distance meter");
}

int WebAdmin::addControl(ControlType controlType, const char* label, const String& value, int parent, char* name)
{
    ControlColor color = ControlColor::None;
    if (name != nullptr) {
        auto callback = [](Control* sender, int eventName, void* userData) { admin->handleCallback(sender, eventName, userData); };

        return ESPUI.addControl(
            controlType, 
            label, 
            value, 
            color, 
            parent,
            callback,
            name
        );
    }

    return ESPUI.addControl(
        controlType, 
        label, 
        value, 
        color, 
        parent
    );
}

void WebAdmin::handleCallback(Control* sender, int eventName, void* userData)
{
    if (userData == nullptr) {
        return;
    }
    if (userData == Parameter::MQTT_DEVICE) {
        this->updateTopics(sender);
    }
    if (userData == WebAdmin::SUBMIT) {
        if (eventName == B_DOWN) {
            return;
        }
        ESP.restart();
        return;
    }
    if (userData == WebAdmin::RESET) {
        if (eventName == B_DOWN) {
            return;
        }
        this->resetCallback();
        return;
    }

    this->storage->saveParameter((char *) userData, sender->value);
}

void WebAdmin::updateTopics(Control* sender)
{
    auto percentageControl = ESPUI.getControl(this->percentageTopicId);
    percentageControl->value = this->getPercentageTopic(sender->value);

    auto distanceControl = ESPUI.getControl(this->distanceTopicId);
    distanceControl->value = this->getDistanceTopic(sender->value); 

    ESPUI.updateControl(percentageControl);
    ESPUI.updateControl(distanceControl);
}

String WebAdmin::getDistanceTopic(String deviceName)
{
    return "Distance topic: " + deviceName + "/stat/distance";
}

String WebAdmin::getPercentageTopic(String deviceName)
{
    return "Percentage topic: " + deviceName + "/stat/percentage";
}

void WebAdmin::run()
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
    String data = buffer;

    this->updateStats(data);
}

void WebAdmin::updateStats(String& data)
{
    auto stats = ESPUI.getControl(this->statsId);
    stats->value = data;

    ESPUI.updateControl(stats);
}
