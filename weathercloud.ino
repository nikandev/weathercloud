#include <Arduino.h>
#include "setup.h"
#include "abstractlogic.h"

AbstractLogic* l;

void setup()
{
    Setup s;
    s.run();
    l = s.result();
}

void loop()
{
    l->run();
}
