#include <EEPROM.h>
#include "credentialsmemory.h"

WifiCredentials CredentialsMemory::read()
{
    Serial.println("Initializing EEPROM");

    EEPROM.begin(512);

    Serial.println("Reading EEPROM ssid");

    String essid = "";

    WifiCredentials result;

    for (int i = 0; i < 32; ++i)
    {
        essid += char(EEPROM.read(i));
    }

    result.ssid = essid;
    
    Serial.println();
    Serial.print("ssid: ");
    Serial.println(result.ssid);
    Serial.println("Reading EEPROM password");

    String epass = "";

    for (int i = 32; i < 96; ++i)
    {
        epass += char(EEPROM.read(i));
    }

    result.pwd = epass;

    Serial.print("PASS: ");
    Serial.println(result.pwd);

    return result;
}

bool CredentialsMemory::write(const String& ssid, const String& password)
{
    if (ssid.length() > 0 && password.length() > 0)
    {
        Serial.println("clearing eeprom");

        for (int i = 0; i < 96; ++i)
        {
            EEPROM.write(i, 0);
        }

        Serial.println(ssid);
        Serial.println("");
        Serial.println(password);
        Serial.println("");

        Serial.println("writing eeprom ssid:");

        for (int i = 0; i < ssid.length(); ++i)
        {
            EEPROM.write(i, ssid[i]);
            Serial.print("Wrote: ");
            Serial.println(ssid[i]);
        }

        Serial.println("writing eeprom pass:");

        for (int i = 0; i < password.length(); ++i)
        {
            EEPROM.write(32 + i, password[i]);
            Serial.print("Wrote: ");
            Serial.println(password[i]);
        }

        EEPROM.commit();

        return false;
    }

    return true;
}