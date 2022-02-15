#include "ledcontroller.h"
#include "ledcolor.h"

LedController::LedController()
{
    LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(_leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
}

void LedController::updateLeds(const Sun &s)
{
    LedColor color = s.color();

    const byte r = color.r();
    const byte g = color.g();
    const byte b = color.b();

    _leds[4].setRGB(r, g, b);
    _leds[5].setRGB(r, g, b);

    FastLED.show();
}

void LedController::updateLeds(const Cloud &c)
{
    LedColor color = c.color();

    const byte r = color.r();
    const byte g = color.g();
    const byte b = color.b();

    _leds[0].setRGB(r, g, b);
    _leds[1].setRGB(r, g, b);
    _leds[2].setRGB(r, g, b);
    _leds[3].setRGB(r, g, b);

    FastLED.show();
}