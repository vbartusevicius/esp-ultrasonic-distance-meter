#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>

class Display
{
    public:
        Display();
        void displayText(String text);
};

#endif