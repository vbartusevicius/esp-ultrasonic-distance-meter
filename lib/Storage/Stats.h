
#ifndef STATS_H
#define STATS_H

#include <Arduino.h>
#include <IPAddress.h>

class Stats
{
    public:
        String wifiSignal = "";
        String ipAddress = "";
        String network = "";
        String uptime = "";
        String relativeDistance = "";

    public:
        Stats();
        void updateStats(float relativeDistance);
};

#endif