#ifndef SUN_H
#define SUN_H

#include <Arduino.h>
#include "ledsettings.h"
#include "ledcolor.h"
#include "weatherdata.h"

class Sun
{
    public:
        Sun();
        void setBrightness(byte b);
        void setState(Temperatures t, int sunriseTimeUtc, int sunsetTimeUtc, int cloudPercentage);
        LedColor color() const;
    private:
        byte _brightness;
        LedColor _color;
};

#endif // SUN_H