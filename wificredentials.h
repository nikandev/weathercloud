#ifndef WIFICREDENTIALS_H
#define WIFICREDENTIALS_H

#include <Arduino.h>

struct WifiCredentials
{
    String ssid = "";
    String pwd = "";
};

#endif