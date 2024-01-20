#include "Logger.h"

Logger::Logger(Stream* stream, const char* channel)
{
    this->channel = channel;
    this->log = new Logging();

    this->log->begin(LOG_LEVEL_VERBOSE, stream, false);
}

void Logger::info(String message)
{
    char buffer[255];
    this->formatMessage(message.c_str(), "INFO", buffer);

    this->log->infoln(buffer);
}

void Logger::formatMessage(const char* message, const char* level, char* buffer)
{
    char timestamp[50];
    this->getTimestamp(timestamp);

    char prefix[100];
    sprintf(prefix, "%s [%s] %s: ", timestamp, this->channel, level);

    strcpy(buffer, prefix);
    strcat(buffer, message);
}

void Logger::getTimestamp(char* buffer)
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
  sprintf(timestamp, "%02d:%02d:%02d.%03d", (int) Hours, (int) Minutes, (int) Seconds, (int) MilliSeconds);
  strcpy(buffer, timestamp);
}