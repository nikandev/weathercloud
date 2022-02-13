#ifndef CURRENTSTATE_H
#define CURRENTSTATE_H

#include <WiFi.h>

struct CurrentState
{
    bool isResetMode;
    WiFiServer wifiServer;
};

#endif