#include <Arduino.h>
#include "setup.h"
#include "logic.h"

Logic* l;

void setup()
{
    Setup s;
    s.run();
    l = new Logic(s.currentState());
}

void loop()
{
    l->run();
}
