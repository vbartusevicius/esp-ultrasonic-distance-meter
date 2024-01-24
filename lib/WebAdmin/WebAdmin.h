#ifndef WEB_ADMIN_H
#define WEB_ADMIN_H

#define WEBSERVER_H
#define HTTP_ANY
#include <ESPAsyncWebServer.h>
#include <ESPUI.h>
#include "Logger.h"
#include "Storage.h"

typedef void (*ResetCallback)();

class WebAdmin
{
    private:
        unsigned int statsId;
        unsigned int distanceTopicId;
        unsigned int logId;
        unsigned int lastUpdated;
        unsigned int interval;
        Storage* storage;
        Logger* logger;
        ResetCallback resetCallback;

        static char* SUBMIT;
        static char* RESET;

    public:
        WebAdmin(Storage* storage, Logger* logger, ResetCallback resetCallback);
        void begin();
        void run();
        void handleCallback(Control* control, int number, void* userData);

    private:
        int addControl(ControlType controlType, const char* label, const String& value, int parent, char* name = nullptr);
        void updateStats();
        void updateLog();
        void updateTopics(String value);
        String getDistanceTopic(String deviceName);
        bool shouldUpdate();
};

#endif