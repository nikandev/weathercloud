#include <Arduino_JSON.h>
#include <ArduinoOTA.h>
#include <HTTPClient.h>
#include "html.h"
#include "mainlogic.h"

MainLogic::MainLogic() 
    : _server(new WiFiServer(80)),
      _led(new LedController)
{
}

void MainLogic::run()
{
    checkWebServer();
    checkWeather();
    ArduinoOTA.handle();
}

void MainLogic::checkWebServer()
{
    WiFiClient client = _server->available();
    processClientRequest(client);
}

void MainLogic::checkWeather()
{ 
    if ((millis() - _lastWeatherRequestTime) > _weatherRequestDelay)
    {
        Weather w = getWeatherCurrent();
        reactToNewWeather(w);
    }
}

void MainLogic::processClientRequest(WiFiClient& client)
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
                    String html = Html::currentWeatherInterface();
                    client.println(html);
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

Weather MainLogic::getWeatherCurrent() // все работает
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

String MainLogic::httpGETRequest(const char* request) // все работает
{
    HTTPClient http;

    http.begin(request);

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

Weather MainLogic::getWeatherInAnHour()
{

}

Weather MainLogic::getWeatherTomorrow()
{

}

void MainLogic::reactToNewWeather(const Weather& w) // Добавить логику изменения цвета в зависимости от погоды
{
    _sun.setState(w.main.tempertatures, w.system.sunriseTimeUtc, w.system.sunsetTimeUtc, w.cloudPercentage);
    _cloud.setState(w.rain, w.snow, w.cloudPercentage);

    _led->updateLeds(_sun);
    _led->updateLeds(_cloud);
}
