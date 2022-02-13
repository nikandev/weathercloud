#ifndef CREDENTIALSMEMORY_H
#define CREDENTIALSMEMORY_H

#include <Arduino.h>
#include "wificredentials.h"

class CredentialsMemory
{
    public:
        static bool write(const String& ssid, const String& password);
        static WifiCredentials read();
};

#endif