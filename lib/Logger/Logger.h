#ifndef LOGGER_H
#define LOGGER_H

#include <ArduinoLog.h>

class Logger
{
    private:
        Logging* log;
        String channel;

    public:
        Logger(Stream* stream, String channel);
        void info(String message);
    
    private:
        static String getLogLevel(Print* _logOutput, int logLevel);
        static String getTimestamp();
        static void printPrefix(Print* _logOutput, int logLevel);
};

#endif
