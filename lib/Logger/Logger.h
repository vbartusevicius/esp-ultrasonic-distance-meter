#ifndef LOGGER_H
#define LOGGER_H

#include <ArduinoLog.h>

class Logger
{
    private:
        Logging* log;
        const char* channel;

    public:
        Logger(Stream* stream, const char* channel);
        void info(String message);
    
    private:
        void formatMessage(const char* message, const char* level, char* buffer);
        void getTimestamp(char* buffer);
        static void printPrefix(Print* _logOutput, int logLevel);
};

#endif
