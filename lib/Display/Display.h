#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>

class Display
{
    private:
        float relativeProgress = 0;
        int progressHeight = 16;
        int displayWidth;

    public:
        Display();
        void run();
        void setProgress(float relative);
    
    private:
        void renderProgress();
};

#endif