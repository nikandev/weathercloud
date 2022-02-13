#ifndef LOGIC_H
#define LOGIC_H
        
#include <Arduino.h>
#include <WiFi.h>
#include <FastLED.h>
#include "weatherdata.h"
#include "currentstate.h"
#include "ledsettings.h"
#include "cloud.h"
#include "sun.h"

class Logic
{
    public:
        Logic(CurrentState state);
        void run();
    private:
        WiFiClient _client;
        WiFiServer _server;
        Sun _sun;
        Cloud _cloud;
        CRGB _leds[NUM_LEDS];
        bool _isResetMode;
        const String OWM_ADDRESS    = "http://api.openweathermap.org/data/2.5/weather";
        const String OWM_API_KEY    = "&appid="; // openweathermap.org/api_keys
        const String OWM_CITY_ID    = "?id=524901"; // openweathermap.org/city/524901 Moscow, RU
        const String OWM_LANGUAGE = "&lang=EN";
        const String OWM_UNITS      = "&units=metric";
        const String OWM_REQUEST_CURRENT = 
            OWM_ADDRESS +
            OWM_CITY_ID +
            OWM_API_KEY +
            OWM_LANGUAGE +
            OWM_UNITS;
        const int _weatherRequestDelay = 60 * 1000; // ms
        int _lastWeatherRequestTime = 0;
        void processClientRequest(WiFiClient& client);
        Weather getWeatherCurrent();
        String httpGETRequest(const char* request);
        Weather getWeatherInAnHour();
        Weather getWeatherTomorrow();
        void setCloudLeds(byte r, byte g, byte b);
        void setSunLeds(byte r, byte g, byte b);
        void checkWebServer();
        void reactToNewWeather(const Weather& w);
        void checkWeather();
};

#endif
