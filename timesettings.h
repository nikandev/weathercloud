#ifndef TIMESETTINGS_H
#define TIMESETTINGS_H

#include <Arduino.h>

struct TimeSettings
{
    const int utcOffset = 3; // Moscow UTC+3
    const int timeZone = utcOffset * 60 * 60;
    const int dst = 0; // DaylightSavingsTime
};

#endif // TIMESETTINGS_H
