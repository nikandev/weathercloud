#include "sun.h"

Sun::Sun()
{
}

void Sun::setBrightness(byte b)
{
    _brightness = b;
}

void Sun::setState(Temperatures t, int sunriseTimeUtc, int sunsetTimeUtc, int cloudPercentage)
{
    _color.setR(255); // Temp
    _color.setG(255);
    _color.setB(0);
}

LedColor Sun::color() const
{
    return _color;
}