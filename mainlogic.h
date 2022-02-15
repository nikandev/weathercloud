#ifndef MAINLOGIC_H
#define MAINLOGIC_H
        
#include <Arduino.h>
#include <WiFi.h>
#include "weatherdata.h"
#include "cloud.h"
#include "sun.h"
#include "ledcontroller.h"
#include "abstractlogic.h"

class MainLogic : public AbstractLogic
{
    public:
        MainLogic();
        void run() override;
    private:
        WiFiServer* _server;
        Sun _sun;
        Cloud _cloud;
        LedController* _led;
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
        void checkWebServer();
        void checkWeather();
        void processClientRequest(WiFiClient& client);
        Weather getWeatherCurrent();
        String httpGETRequest(const char* request);
        Weather getWeatherInAnHour();
        Weather getWeatherTomorrow();
        void reactToNewWeather(const Weather& w);
};

#endif // MAINLOGIC_H
