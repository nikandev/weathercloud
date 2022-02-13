#ifndef LEDSETTINGS_H
#define LEDSETTINGS_H

#include <Arduino.h>
#include <FastLED.h>

struct LedColor
{
    int r;
    int g;
    int b;
};

#define NUM_LEDS        8
#define LED_PIN         11 // D35 - GPIO35
#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB
#define BRIGHTNESS      250

#endif