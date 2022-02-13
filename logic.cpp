#include <Arduino_JSON.h>
#include <ArduinoOTA.h>
#include <FastLED.h>
#include <HTTPClient.h>
#include "html.h"
#include "logic.h"

Logic::Logic(CurrentState state) 
    : _isResetMode(state.isResetMode),
      _server(state.wifiServer)
{
}

void Logic::run()
{
    if (_isResetMode)
    {
        WiFiClient client = _server.available();
        processClientRequest(client);
        return;
    }

    checkWebServer();
    checkWeather();
    ArduinoOTA.handle();
}

void Logic::processClientRequest(WiFiClient& client)
{
    if (client)
    {
        Serial.println("\n[Client connected]");

        while (client.connected())
        {
            if (client.available())
            {
                String request = client.readStringUntil('\r');
                Serial.print(request);

                if (request.length() == 1 && request[0] == '\n')
                {
                    client.println(Html::htmlSSIDInputForm());
                    break;
                }
            }
        }

        while (client.available())
        {
            client.read();
        }

        client.stop();
        Serial.println("[Client disconnected]");
    }
}

Weather Logic::getWeatherCurrent() // все работает
{
    Serial.println("Getting current weather data...");

    String jsonBuffer;
    Weather w;

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi is Disconnected");
        return w;
    }

    jsonBuffer = httpGETRequest(OWM_REQUEST_CURRENT.c_str());

    JSONVar jsonWeatherData = JSON.parse(jsonBuffer);

    if (JSON.typeof(jsonWeatherData) == "undefined")
    {
        Serial.println("Parsing input failed!");
        return w;
    }

    WeatherData wd(jsonWeatherData);

    w = wd.weather();

    _lastWeatherRequestTime = millis();

    Serial.println("Data parsed");
}

String Logic::httpGETRequest(const char* request) // все работает
{
    HTTPClient http;

    http.begin(_client, request);

    int httpResponseCode = http.GET();

    String payload = "{}";

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else
    {
        Serial.print("HTTP Response error code: ");
        Serial.println(httpResponseCode);
    }

    http.end();

    return payload;
}

Weather Logic::getWeatherInAnHour()
{

}

Weather Logic::getWeatherTomorrow()
{

}

void Logic::setCloudLeds(byte r, byte g, byte b)
{
    _leds[0].setRGB(r, g, b);
    _leds[1].setRGB(r, g, b);
    _leds[2].setRGB(r, g, b);
    _leds[3].setRGB(r, g, b);

    FastLED.show();
}

void Logic::setSunLeds(byte r, byte g, byte b)
{
    _leds[4].setRGB(r, g, b);
    _leds[5].setRGB(r, g, b);

    FastLED.show();
}

void Logic::checkWebServer() // Todo: Отрисовать страницу, забрать параметры
{

}

void Logic::reactToNewWeather(const Weather& w) // Добавить логику изменения цвета в зависимости от погоды
{
    // _sun.setState(w.main.tempertatures, w.system.sunriseTimeUtc, w.system.sunsetTimeUtc, w.cloudPercentage);
    // _cloud.setState(w.rain, w.snow, w.cloudPercentage);

    // setCloudLeds(_cloud.color()); // Todo: Не так - чтобы была анимация, leds должны быть внутри этих классов
    // setSunLeds(_sun.color());
}

void Logic::checkWeather()
{ 
    if ((millis() - _lastWeatherRequestTime) > _weatherRequestDelay)
    {
        Weather w = getWeatherCurrent();
        reactToNewWeather(w);
    }
}
