#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "MqttClient.h"
#include "Parameter.h"

extern WiFiClient network;

MqttClient::MqttClient(Storage* storage, Logger* logger)
{
    this->storage = storage;
    this->logger = logger;

    this->lastReconnectAttempt = 0;
}

bool MqttClient::connect()
{
    String username = this->storage->getParameter(Parameter::MQTT_USER);
    String password = this->storage->getParameter(Parameter::MQTT_PASS);
    String device = this->storage->getParameter(Parameter::MQTT_DEVICE);

    std::function<bool()> connection;

    if (username == "" && password == "") {
        connection = [device, this]() -> bool { 
            return client.connect(device.c_str()); 
        };
    } else {
        connection = [device, username, password, this]() -> bool {
            return client.connect(device.c_str(), username.c_str(), password.c_str());
        };
    }

    auto result = connection();

    if (result) {
        this->logger->info("Conected to MQTT.");
    } else {
        this->logger->warning("Failed to connect to MQTT.");
    }

    return result;
}

void MqttClient::begin()
{
    client.begin(
        this->storage->getParameter(Parameter::MQTT_HOST).c_str(),
        atoi(this->storage->getParameter(Parameter::MQTT_PORT).c_str()),
        network
    );

    this->connect();
}

bool MqttClient::run()
{
    client.loop();
    delay(10);

    if (client.connected()) {
        return true;
    }
    
    this->logger->warning("Connection to MQTT lost, reconnecting.");

    return this->connect();
}

void MqttClient::sendDistance(float relative, float absolute, float measured)
{
    JsonDocument doc;
    String json;

    doc["relative"] = relative;
    doc["absolute"] = absolute;
    doc["measured"] = measured;
    serializeJson(doc, json);

    auto ok = client.publish(this->storage->getParameter(Parameter::MQTT_TOPIC_DISTANCE).c_str(), json);

    if (!ok) {
        this->logger->warning("Failed to publish to MQTT: " + json);
    }
}
