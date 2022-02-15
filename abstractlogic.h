#ifndef ABSTRACTLOGIC_H
#define ABSTRACTLOGIC_H

#include <Arduino.h>

class AbstractLogic
{
    public:
        virtual void run() = 0;
};

#endif // ABSTRACTLOGIC_H
