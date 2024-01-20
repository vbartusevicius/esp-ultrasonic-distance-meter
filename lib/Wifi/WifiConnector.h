#include <WiFiManager.h>
#include "Logger.h"

class WifiConnector
{
    private:
        WiFiManager* wm;
        Logger* logger;

    public:
        WifiConnector(Logger* logger);
        bool process();
        bool connect();
};
