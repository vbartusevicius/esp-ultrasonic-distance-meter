#ifndef PARAMETER_H
#define PARAMETER_H

class Parameter
{
    public:
        static char* DISTANCE_EMPTY;
        static char* DISTANCE_FULL;
        static char* MQTT_HOST;
        static char* MQTT_PORT;
        static char* MQTT_USER;
        static char* MQTT_PASS;
        static char* MQTT_DEVICE;
};

char* Parameter::DISTANCE_EMPTY = "distance_empty";
char* Parameter::DISTANCE_FULL = "distance_full";
char* Parameter::MQTT_HOST = "mqtt_host";
char* Parameter::MQTT_PORT = "mqtt_port";
char* Parameter::MQTT_USER = "mqtt_user";
char* Parameter::MQTT_PASS = "mqtt_pass";
char* Parameter::MQTT_DEVICE = "mqtt_device";

#endif
