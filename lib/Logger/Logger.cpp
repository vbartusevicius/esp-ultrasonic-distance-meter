#include "Logger.h"

Logger* logger = nullptr;

Logger::Logger(Stream* stream, String channel)
{
    this->channel = channel;
    this->log = new Logging();
    this->log->setPrefix(&Logger::staticPrefixFunction);

    this->log->begin(LOG_LEVEL_VERBOSE, stream, false);
}

void Logger::info(String message)
{
    this->log->infoln(message.c_str());
}

void Logger::staticPrefixFunction(Print* _logOutput, int logLevel) 
{
    if (logger) {
        logger->printPrefix(_logOutput, logLevel);
    }
}

void Logger::printPrefix(Print* _logOutput, int logLevel)
{
    Logger::printTimestamp(_logOutput);
    Logger::printChannel(_logOutput);
    Logger::printLogLevel(_logOutput, logLevel);
}

void Logger::printTimestamp(Print* _logOutput)
{
    const unsigned long MSECS_PER_SEC = 1000;
    const unsigned long SECS_PER_MIN = 60;
    const unsigned long SECS_PER_HOUR = 3600;
    const unsigned long SECS_PER_DAY = 86400;

    const unsigned long msecs =  millis();
    const unsigned long secs =  msecs / MSECS_PER_SEC;

    const unsigned long MilliSeconds =  msecs % MSECS_PER_SEC;
    const unsigned long Seconds =  secs % SECS_PER_MIN ;
    const unsigned long Minutes = (secs / SECS_PER_MIN) % SECS_PER_MIN;
    const unsigned long Hours = (secs % SECS_PER_DAY) / SECS_PER_HOUR;

    char timestamp[20];
    sprintf(timestamp, "%02d:%02d:%02d.%03d ", (int) Hours, (int) Minutes, (int) Seconds, (int) MilliSeconds);
    _logOutput->print(timestamp);
}

void Logger::printChannel(Print* _logOutput)
{
    _logOutput->print("[" + this->channel + "] ");
}

void Logger::printLogLevel(Print* _logOutput, int logLevel)
{
    String level = "";
    switch (logLevel)
    {
        default:
        case 0: level = "SILENT"; break;
        case 1: level = "FATAL"; break;
        case 2: level = "ERROR"; break;
        case 3: level = "WARNING"; break;
        case 4: level = "INFO"; break;
        case 5: level = "TRACE"; break;
        case 6: level = "VERBOSE"; break;
    }
    _logOutput->print(level + ": ");
}
