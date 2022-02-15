#ifndef CLOUD_H
#define CLOUD_H

#include <Arduino.h>
#include "ledsettings.h"
#include "ledcolor.h"
#include "weatherdata.h"

class Cloud
{
    public:
        Cloud();
        void setBrightness(byte value);
        void setState(Rain r, Snow s, int cloudPercentage);
        LedColor color() const;
    private:
        byte _brightness;
        LedColor _color;
};

#endif // CLOUD_H