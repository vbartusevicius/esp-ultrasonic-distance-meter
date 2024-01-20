#define WEBSERVER_H
#define HTTP_ANY
#include <ESPAsyncWebServer.h>
#include <ESPUI.h>
#include "Logger.h"

class WebAdmin
{
    private:
        unsigned int statsId;
        unsigned int lastUpdated;
        unsigned int interval;

    public:
        WebAdmin();
        void renderAdmin();
        void updateAdmin();
};
