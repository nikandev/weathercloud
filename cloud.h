#ifndef CLOUD_H
#define CLOUD_H

#include <Arduino.h>
#include "ledsettings.h"
#include "weatherdata.h"

enum State
{
    Default = 0,
    Sunny = 1,
    Rainy = 2,
    Cloudy = 3,
    Lightning = 4,
    Snowing = 5
}

class Cloud
{
    public:
        Cloud();
        void setBrightness(int value);
        void setState(Rain r, Snow s, int cloudPercentage);
        LedColor color();
    private:
        State _s;
        int _brightness;
        LedColor _color;
}

#endif