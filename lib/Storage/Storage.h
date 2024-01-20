#ifndef STORAGE_H
#define STORAGE_H

#include <Preferences.h>

class Storage
{
    private:
        Preferences* prefs;
    
    public:
        Storage();
        void begin();
};

#endif