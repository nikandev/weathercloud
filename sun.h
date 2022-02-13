#ifndef SUN_H
#define SUN_H

#include <Arduino.h>
#include "ledsettings.h"

enum State
{
    Default = 0,
    Sunny = 1,
    Rainy = 2,
    Night = 3
}

class Sun
{
    public:
        Sun();
        void setBrightness(int value);
        void setState(Temperatures t, int sunriseTimeUtc, int sunsetTimeUtc, int cloudPercentage);
        LedColor color();
    private:
        State _s;
        int _brightness;
        LedColor _color;
}

#endif