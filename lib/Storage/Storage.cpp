#include "Storage.h"

Storage::Storage()
{
    this->prefs = new Preferences();
}

void Storage::begin()
{
    this->prefs->begin("esp_distance_meter");
}
