#include <WiFiManager.h>
#include "Logger.h"

class WifiConnector
{
    private:
        WiFiManager* wm;
        Logger* logger;
        const char* appName;

    public:
        WifiConnector(Logger* logger);
        void process();
        bool connect();
};
