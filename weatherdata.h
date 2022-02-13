#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <Arduino.h>
#include <Arduino_JSON.h>

struct Coordinates
{
    float latitude;
    float longtitude;
};

struct Temperatures
{
    float current;
    float feelsLike;
    float minimum;
    float maximum;
};

struct Main
{
    Temperatures tempertatures;
    int pressure;
    int humidity;
    int seaLevel;
    int groundLevel;
    int visibility;
};

struct Rain
{
    int oneHourVolumeInMm;
    int threeHourVolumeInMm;
};

struct Snow
{
    int oneHourVolumeInMm;
    int threeHourVolumeInMm;
};

struct Wind
{
    float speed;
    int deg;
    float gust;
};

struct Sys
{
    int type;
    int id;
    String message;
    String country;
    int sunriseTimeUtc;
    int sunsetTimeUtc;
};

struct Weather
{
    int id;
    Main main;
    String description;
    int iconId;
    String base;
    Wind wind;
    int cloudPercentage;
    Rain rain;
    Snow snow;
    int timeOfDataCalcUtc;
    Sys system;
    int timeZone;
    int cityId;
    String cityName;
    int internal;
};

class WeatherData
{
    public:
        WeatherData(const JSONVar& jsonWeatherData);
        Weather weather();
    private:
        Weather _w;
};

#endif