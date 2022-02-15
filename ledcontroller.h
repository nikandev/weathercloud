#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>
#include <FastLED.h>
#include "ledsettings.h"
#include "sun.h"
#include "cloud.h"

class LedController
{
    public:
        LedController();
        void updateLeds(const Sun& s);
        void updateLeds(const Cloud& c);
    private:
        CRGB _leds[NUM_LEDS];
};

#endif // LEDCONTROLLER_H