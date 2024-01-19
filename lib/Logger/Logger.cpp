#include "Logger.h"

Logger::Logger(Stream* stream, String channel)
{
    this->channel = channel;
    this->log = new Logging();

    this->log->setPrefix(Logger::printPrefix);

    this->log->begin(LOG_LEVEL_INFO, stream, false);
}

void Logger::info(String message)
{
    this->log->infoln(message.c_str());
}

void Logger::printPrefix(Print* _logOutput, int logLevel)
{
    auto timestamp = Logger::getTimestamp();
    auto level = Logger::getLogLevel(_logOutput, logLevel);

    _logOutput->write((timestamp + " [" + level + "] ").c_str());
}

String Logger::getTimestamp()
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
  const unsigned long Hours = (secs  % SECS_PER_DAY) / SECS_PER_HOUR;

  char timestamp[20];
  sprintf(timestamp, "%02d:%02d:%02d.%03d", (int) Hours, (int) Minutes, (int) Seconds, (int) MilliSeconds);
  
  return String(timestamp);
}

String Logger::getLogLevel(Print* _logOutput, int logLevel)
{
    switch (logLevel)
    {
        default:
        case 0: return "SILENT";
        case 1: return "FATAL";
        case 2: return "ERROR";
        case 3: return "WARNING";
        case 4: return "INFO";
        case 5: return "TRACE";
        case 6: return "VERBOSE";
    }   
}