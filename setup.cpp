#include <ArduinoOTA.h>
#include <time.h>
#include "setup.h"
#include "timesettings.h"
#include "credentialsmemory.h"

#define RESET_BUTTON_PIN 4 // D2 - GPIO4 Нажатие - размыкание с земли, замыкание на 3v.

Setup::Setup() : _isResetMode(false)
{
}

void Setup::run()
{
    setupSerial();

    if (isResetMode())
    {
        setupAP();
        processReset();
    }
    else
    {
        processMain();
    }
}

AbstractLogic* Setup::result()
{
    return _result;
}

void Setup::setupSerial()
{
    Serial.begin(115200);
    Serial.println("Setting up...");
    delay(500);
}

bool Setup::isResetMode()
{
    pinMode(RESET_BUTTON_PIN, INPUT);

    if (digitalRead(RESET_BUTTON_PIN) == HIGH)
    {
        Serial.println("Reset Mode is active");
        return true;
    }

    return false;
}

void Setup::setupAP()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("ssid: Cloud");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Cloud");

    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());
}

void Setup::processReset()
{
    _isResetMode = true;
    _result = new ResetLogic();
}

void Setup::processMain()
{
    Serial.println("Normal mode is active");
    WiFi.softAPdisconnect(true);

    WifiCredentials fromMemory;
    fromMemory = CredentialsMemory::read();

    connectWifi(fromMemory);
    setupArduinoOTA();

    TimeSettings ts;

    configTime(ts.timeZone, ts.dst, "pool.ntp.org", "time.nist.gov");

    _result = new MainLogic();

    Serial.println("Setup complete.");
}

void Setup::connectWifi(WifiCredentials credentials) // все работает
{
    const char* ssid = credentials.ssid.c_str();
    const char* pwd = credentials.pwd.c_str();

    WiFi.begin(ssid, pwd);
    Serial.print("Connecting to ");
    Serial.println(ssid);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.println(WiFi.localIP());
    Serial.println();
}

void Setup::setupWifiCredentials()
{
    Serial.println("Lighting up built-in led");
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP("Cloud", "12345678") ? "Ready" : "Failed!");
    Serial.println("ssid: Cloud, password: 12345678");
}

void Setup::setupArduinoOTA() // Проверить
{
    ArduinoOTA.onStart([]()
    {
        String type;

        if (ArduinoOTA.getCommand() == U_FLASH)
        {
            type = "sketch";
        }
        else // U_FS
        {
            type = "filesystem";
        }

        // NOTE: if updating FS this would be the place to unmount FS using FS.end()
        Serial.println("Start updating " + type);
    });

    ArduinoOTA.onEnd([]()
    {
        Serial.println("\nEnd");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error)
    {
        Serial.printf("Error[%u]: ", error);

        if (error == OTA_AUTH_ERROR)
        {
            Serial.println("Auth Failed");
        }
        else if (error == OTA_BEGIN_ERROR)
        {
            Serial.println("Begin Failed");
        }
        else if (error == OTA_CONNECT_ERROR)
        {
            Serial.println("Connect Failed");
        }
        else if (error == OTA_RECEIVE_ERROR)
        {
            Serial.println("Receive Failed");
        }
        else if (error == OTA_END_ERROR)
        {
            Serial.println("End Failed");
        }
    });

    ArduinoOTA.begin();
}
