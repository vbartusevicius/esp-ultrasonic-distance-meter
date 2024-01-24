#include "Storage.h"

Storage::Storage()
{
    this->prefs = new Preferences();
}

void Storage::begin()
{
    this->prefs->begin("esp_distance_meter");
}

void Storage::saveParameter(char* name, String& value)
{
    Serial.println(name);
    Serial.println(value);
    this->prefs->putString(name, value);
}

String Storage::getParameter(char* name, String defaultValue)
{
    return this->prefs->getString(name, defaultValue);
}

void Storage::reset()
{
    this->prefs->clear();
}
