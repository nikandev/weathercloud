#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPClient.h>
#include <time.h>
#include <FastLED.h>
#include <Arduino_JSON.h>

//Wifi

const char* _ssid     = "";
const char* _password = "";

WiFiClient _wifiClient;

//Web page
WiFiServer _webServer(80);
String _HttpRequestHeader;
String _foundNetworksHtml;

const int _webRequestDelay = 2 * 1000; //ms
int _lastWebRequestTime = 0;

//Leds

#define NUM_LEDS    6
#define LED_PIN     14 //D5 - GPIO14
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  250

CRGB _leds[NUM_LEDS];

//Reset button

#define RESET_BUTTON_PIN 4 //D2 - GPIO4 Нажатие - размыкание с земли, замыкание на 3v.
bool _isResetMode = false;

//Weather request

const String OWM_ADDRESS  = "http://api.openweathermap.org/data/2.5/weather";
const String OWM_API_KEY  = "&appid="; // openweathermap.org/api_keys
const String OWM_CITY_ID  = "?id=524901"; // openweathermap.org/city/524901 Moscow, RU
const String OWM_LANGUAGE = "&lang=EN";
const String OWM_UNITS    = "&units=metric";
const String OWM_REQUEST_CURRENT = OWM_ADDRESS +
                                   OWM_CITY_ID +
                                   OWM_API_KEY +
                                   OWM_LANGUAGE +
                                   OWM_UNITS;

const int _weatherRequestDelay = 60 * 1000; //ms
int _lastWeatherRequestTime = 0;

//Time

const int _utcOffset = 3; //Moscow UTC+3
int _timeZone = _utcOffset * 60 * 60;
const int _dst = 0; //DaylightSavingsTime

//Weather data structure

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

void connectWifi() //все работает
{
  WiFi.begin(_ssid, _password);
  Serial.print("Connecting to ");
  Serial.println(_ssid);

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

String httpGETRequest(const char* request) //все работает
{
  HTTPClient http;

  http.begin(_wifiClient, request);

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

Weather getWeatherCurrent() //все работает
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

  Coordinates coord;
  coord.latitude = (double)jsonWeatherData["coord"]["lat"];
  coord.longtitude = (double)jsonWeatherData["coord"]["lon"];

  w.id = (int)jsonWeatherData["weather"]["id"];

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

  w.main = m;

  w.description = JSON.stringify(jsonWeatherData["weather"]["description"]);
  w.iconId = (int)jsonWeatherData["weather"]["icon"];
  w.base = JSON.stringify(jsonWeatherData["base"]);

  Wind wnd;
  wnd.speed = (double)jsonWeatherData["wind"]["speed"];
  wnd.deg = (int)jsonWeatherData["wind"]["deg"];
  wnd.gust = (double)jsonWeatherData["wind"]["gust"];

  w.wind = wnd;

  w.cloudPercentage = (int)jsonWeatherData["clouds"]["all"];

  Rain r;
  r.oneHourVolumeInMm = (int)jsonWeatherData["rain"]["1h"];
  r.threeHourVolumeInMm = (int)jsonWeatherData["rain"]["3h"];

  w.rain = r;

  Snow s;
  s.oneHourVolumeInMm = (int)jsonWeatherData["snow"]["1h"];
  s.threeHourVolumeInMm = (int)jsonWeatherData["snow"]["3h"];

  w.snow = s;

  w.timeOfDataCalcUtc = (int)jsonWeatherData["dt"];

  Sys syst;
  syst.type = (int)jsonWeatherData["sys"]["type"];
  syst.id = (int)jsonWeatherData["sys"]["id"];
  syst.message = JSON.stringify(jsonWeatherData["sys"]["message"]);
  syst.country = JSON.stringify(jsonWeatherData["sys"]["country"]);
  syst.sunriseTimeUtc = (int)jsonWeatherData["sys"]["sunrise"];
  syst.sunsetTimeUtc = (int)jsonWeatherData["sys"]["sunset"];

  w.system = syst;

  w.timeZone = (int)jsonWeatherData["timezone"];
  w.cityId = (int)jsonWeatherData["id"];
  w.cityName = JSON.stringify(jsonWeatherData["name"]);
  w.internal = (int)jsonWeatherData["cod"];

  _lastWeatherRequestTime = millis();

  Serial.println("Data parsed");
}

Weather getWeatherInAnHour()
{

}

Weather getWeatherTomorrow()
{

}

void setCloudLeds(int r, int g, int b)
{
  for (int i = 0; i < 3; i++)
  {
    _leds[i].setRGB(r, g, b);
  }

  FastLED.show();
}

void setSunLeds(int r, int g, int b)
{
  _leds[4].setRGB(r, g, b);
  _leds[5].setRGB(r, g, b);

  FastLED.show();
}

void readEEPROMssid()
{
  Serial.println("Initializing EEPROM");

  EEPROM.begin(512);

  Serial.println("Reading EEPROM ssid");

  String essid = "";

  for (int i = 0; i < 32; ++i)
  {
    essid += char(EEPROM.read(i));
  }
  _ssid = essid.c_str();

  Serial.println();
  Serial.print("ssid: ");
  Serial.println(essid);
  Serial.println("Reading EEPROM password");

  String epass = "";

  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }

  _password = epass.c_str();

  Serial.print("PASS: ");
  Serial.println(epass);
}

int writeEEEPROMssid(const String& ssid, const String& password)
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

      return 0;
    }
    else
    {
        return 1;
    }
}

void setupWifiCredentials()
{
  Serial.println("Lighting up built-in led");
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("Cloud 01", "12345678") ? "Ready" : "Failed!");
  Serial.println("ssid: Cloud 01, password: 12345678");
}

void setupArduinoOTA() //Проверить
{
  ArduinoOTA.onStart([]()
  {
    String type;

    if (ArduinoOTA.getCommand() == U_FLASH)
    {
      type = "sketch";
    }
    else
    { // U_FS
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

void checkWebServer() //Отрисовать страницу, забрать параметры
{

}

void reactToNewWeather(const Weather& w) //Добавить логику изменения цвета в зависимости от погоды
{

}

void checkWeather()
{
  if ((millis() - _lastWeatherRequestTime) > _weatherRequestDelay)
  {
    Weather w = getWeatherCurrent();

    reactToNewWeather(w);
  }
}

void reactToReset()
{
  _isResetMode = true;
  setupAP();
  _webServer.begin();
}

void setupAP()
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
   _foundNetworksHtml += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
   _foundNetworksHtml += "</li>";
  }

  _foundNetworksHtml += "</ol>";

  Serial.println("ssid: Cloud 01");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Cloud 01");

  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
}

String htmlSSIDInputForm()
{
    String htmlPage;
    htmlPage.reserve(1024);

    htmlPage = "HTTP/1.1 200 OK\r\n"
               "Content-Type: text/html; charset=utf-8\r\n"
               "Connection: close\r\n"
               "\r\n"
               "<!DOCTYPE HTML>"
               "<html>"
               "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
               "<h2 style=\"text-align: center\">Добро пожаловать. Снова. :3</h2>"
                    "<table align=\"center\" >"
                       "<tbody>"
                            "<tr>"
                                "<td align=\"right\">SSID:</td>"
                                "<form>"
                                "<td align=\"left\"><input name=\"ssid\" type=\"text\" /></td>"
                                "<form/>"
                            "</tr>"
                            "<tr>"
                                "<td align=\"right\">Пароль:</td>"
                                "<form>"
                                "<td align=\"left\"><input name=\"password\" type=\"text\" /></td>"
                                "<form/>"
                            "</tr>"
                         "</tbody>"
                   "</table>"
               "<form>"
               "<p style=\"text-align: center;\"><input type=\"submit\" value=\"Сохранить\" /></p>";
               "<form>"
               "</html>"
               "\r\n";

    return htmlPage;
}

void processClientRequest(WiFiClient& client)
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
                  client.println(htmlSSIDInputForm());
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

void setup()
{
  Serial.println("Setting up...");
  Serial.begin(115200);
  delay(500);

  pinMode(RESET_BUTTON_PIN, INPUT);

  if (digitalRead(RESET_BUTTON_PIN) == HIGH)
  {
    Serial.println("Reset Mode is active");
    reactToReset();
    return;
  }

  Serial.println("Normal mode is active");

  WiFi.softAPdisconnect(true);

  readEEPROMssid();
  connectWifi();
  setupArduinoOTA();
  _webServer.begin();

  LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(_leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  configTime(_timeZone, _dst, "pool.ntp.org", "time.nist.gov");
  Serial.println("Setup complete.");
}

void loop()
{
  if (_isResetMode)
  {
      WiFiClient client = _webServer.available();
      processClientRequest(client);
      return;
  }

  checkWebServer();
  checkWeather();
  ArduinoOTA.handle();
}
