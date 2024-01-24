#include "Logger.h"

using namespace std;

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

void Logger::warning(String message)
{
    char buffer[255];
    this->formatMessage(message.c_str(), "WARNING", buffer);

    this->log->warningln(buffer);
}

void Logger::error(String message)
{
    char buffer[255];
    this->formatMessage(message.c_str(), "ERROR", buffer);

    this->log->errorln(buffer);
}

vector<String> Logger::getBuffer()
{
    return this->buffer;
}

void Logger::formatMessage(const char* message, const char* level, char* buffer)
{
    char timestamp[50];
    TimeHelper::getTimestamp(timestamp);

    char prefix[100];
    sprintf(prefix, "%s [%s] %s: ", timestamp, this->channel, level);

    strcpy(buffer, prefix);
    strcat(buffer, message);

    if (this->buffer.size() >= 25) {
        this->buffer.erase(this->buffer.begin());
    }
    this->buffer.push_back(buffer);
}
