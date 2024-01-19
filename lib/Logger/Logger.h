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
        static void printPrefix(Print* _logOutput, int logLevel);
        static void printLogLevel(Print* _logOutput, int logLevel);
        static void printTimestamp(Print* _logOutput);
        static void printChannel(Print* _logOutput, char* channel);
};

#endif
