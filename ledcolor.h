#ifndef LEDCOLOR_H
#define LEDCOLOR_H

#include <Arduino.h>

class LedColor
{
    public:
        void setR(byte r) { _r = r; }
        void setG(byte g) { _g = g; }
        void setB(byte b) { _b = b; }
        byte r() const { return _r; }
        byte g() const { return _g; }
        byte b() const { return _b; }
    private:
        byte _r;
        byte _g;
        byte _b;
};

#endif // LEDCOLOR_H