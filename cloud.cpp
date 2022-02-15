#include "cloud.h"

Cloud::Cloud()
{
}

void Cloud::setBrightness(byte b)
{
    _brightness = b;
}

void Cloud::setState(Rain r, Snow s, int cloudPercentage)
{
    _color.setR(255); // Temp
    _color.setG(255);
    _color.setB(255);
}

LedColor Cloud::color() const
{
    return _color;
}