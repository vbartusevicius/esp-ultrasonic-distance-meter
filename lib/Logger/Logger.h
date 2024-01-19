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
};

void printPrefix(Print* _logOutput, int logLevel);
void printTimestamp(Print* _logOutput);
void printLogLevel(Print* _logOutput, int logLevel);

#endif
