#include <ArduinoOTA.h>
#include <time.h>
#include "setup.h"
#include "ledsettings.h"
#include "timesettings.h"
#include "credentialsmemory.h"

#define RESET_BUTTON_PIN 4 // D2 - GPIO4 Нажатие - размыкание с земли, замыкание на 3v.

Setup::Setup() : _server(80), _isResetMode(false)
{
}

void Setup::run()
{
    setupSerial();

    if (isResetMode())
    {
        reactToReset();
        return;
    }

    Serial.println("Normal mode is active");
    WiFi.softAPdisconnect(true);

    WifiCredentials fromMemory;
    fromMemory = CredentialsMemory::read();

    connectWifi(fromMemory);
    setupArduinoOTA();
    _server.begin();

    CRGB leds[NUM_LEDS];
    LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    TimeSettings ts;

    configTime(ts.timeZone, ts.dst, "pool.ntp.org", "time.nist.gov");
    Serial.println("Setup complete.");
}

CurrentState Setup::currentState()
{
    CurrentState result;
    result.isResetMode = _isResetMode;
    result.wifiServer = _server;

    return result;
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

void Setup::reactToReset()
{
    _isResetMode = true;
    setupAP();
    _server.begin();
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

void Setup::setupAP()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    int foundNetworkCount = WiFi.scanNetworks();
    Serial.println("Near network scan completed");

    Serial.println(foundNetworkCount ? "Networks found" : "No WiFi Networks found");

    _foundNetworksHtml = "<ol>";

    for (int i = 0; i < foundNetworkCount; ++i)
    {
        _foundNetworksHtml += "<li>";
        _foundNetworksHtml += WiFi.SSID(i);
        _foundNetworksHtml += " (";
        _foundNetworksHtml += WiFi.RSSI(i);
        _foundNetworksHtml += ")";
        _foundNetworksHtml += (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*";
        _foundNetworksHtml += "</li>";
    }

    _foundNetworksHtml += "</ol>";

    Serial.println("ssid: Cloud");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Cloud");

    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());
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