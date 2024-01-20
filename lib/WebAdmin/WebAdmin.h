#define WEBSERVER_H
#define HTTP_ANY
#ifndef WEB_ADMIN_H
#define WEB_ADMIN_H
#include <ESPAsyncWebServer.h>
#include <ESPUI.h>
#include "Logger.h"
#include "Storage.h"

class WebAdmin
{
    private:
        unsigned int statsId;
        unsigned int lastUpdated;
        unsigned int interval;
        Storage* storage;

    public:
        WebAdmin(Storage* storage);
        void begin();
        void run();
        void handleCallback(Control* control, int number, void* userData);
};

#endif