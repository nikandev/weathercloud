#include "weatherdata.h"

WeatherData::WeatherData(const JSONVar& jsonWeatherData)
{
    Coordinates coord;
    coord.latitude = (double)jsonWeatherData["coord"]["lat"];
    coord.longtitude = (double)jsonWeatherData["coord"]["lon"];

    _w.id = (int)jsonWeatherData["weather"]["id"];

    Main m;

    Temperatures t;
    t.current = (double)jsonWeatherData["main"]["temp"];
    t.feelsLike = (double)jsonWeatherData["main"]["feels_like"];
    t.minimum = (double)jsonWeatherData["main"]["temp_min"];
    t.maximum = (double)jsonWeatherData["main"]["temp_max"];

    m.tempertatures = t;

    m.pressure = (int)jsonWeatherData["main"]["pressure"];
    m.humidity = (int)jsonWeatherData["main"]["humidity"];
    m.seaLevel = (int)jsonWeatherData["main"]["sea_level"];
    m.groundLevel = (int)jsonWeatherData["main"]["grnd_level"];
    m.visibility = (int)jsonWeatherData["visability"];

    _w.main = m;

    _w.description = JSON.stringify(jsonWeatherData["weather"]["description"]);
    _w.iconId = (int)jsonWeatherData["weather"]["icon"];
    _w.base = JSON.stringify(jsonWeatherData["base"]);

    Wind wnd;
    wnd.speed = (double)jsonWeatherData["wind"]["speed"];
    wnd.deg = (int)jsonWeatherData["wind"]["deg"];
    wnd.gust = (double)jsonWeatherData["wind"]["gust"];

    _w.wind = wnd;

    _w.cloudPercentage = (int)jsonWeatherData["clouds"]["all"];

    Rain r;
    r.oneHourVolumeInMm = (int)jsonWeatherData["rain"]["1h"];
    r.threeHourVolumeInMm = (int)jsonWeatherData["rain"]["3h"];

    _w.rain = r;

    Snow s;
    s.oneHourVolumeInMm = (int)jsonWeatherData["snow"]["1h"];
    s.threeHourVolumeInMm = (int)jsonWeatherData["snow"]["3h"];

    _w.snow = s;

    _w.timeOfDataCalcUtc = (int)jsonWeatherData["dt"];

    Sys syst;
    syst.type = (int)jsonWeatherData["sys"]["type"];
    syst.id = (int)jsonWeatherData["sys"]["id"];
    syst.message = JSON.stringify(jsonWeatherData["sys"]["message"]);
    syst.country = JSON.stringify(jsonWeatherData["sys"]["country"]);
    syst.sunriseTimeUtc = (int)jsonWeatherData["sys"]["sunrise"];
    syst.sunsetTimeUtc = (int)jsonWeatherData["sys"]["sunset"];

    _w.system = syst;

    _w.timeZone = (int)jsonWeatherData["timezone"];
    _w.cityId = (int)jsonWeatherData["id"];
    _w.cityName = JSON.stringify(jsonWeatherData["name"]);
    _w.internal = (int)jsonWeatherData["cod"];
}

Weather WeatherData::weather()
{
    return _w;
}