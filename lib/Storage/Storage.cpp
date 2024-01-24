#include "Storage.h"

Storage::Storage()
{
}

void Storage::begin()
{
    prefs.begin("esp_distance_meter");
}

void Storage::saveParameter(char* name, String& value)
{
    prefs.putString(name, value);
}

String Storage::getParameter(char* name, String defaultValue)
{
    return prefs.getString(name, defaultValue);
}

void Storage::reset()
{
    prefs.clear();
}
