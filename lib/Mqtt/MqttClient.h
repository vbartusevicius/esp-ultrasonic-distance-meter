#ifndef MY_MQTT_CLIENT_H
#define MY_MQTT_CLIENT_H

#include <MQTT.h>
#include "Storage.h"
#include "Logger.h"

class MqttClient
{
    private:
        Storage* storage;
        Logger* logger;
        MQTTClient* client;
        unsigned long lastReconnectAttempt;

    public:
        MqttClient(Storage* storage, Logger* logger);
        void begin();
        bool connect();
        void run();
        void sendDistance(float relative, float absolute);
};

#endif