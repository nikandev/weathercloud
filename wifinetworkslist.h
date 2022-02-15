#ifndef WIFINETWORKSLIST_H
#define WIFINETWORKSLIST_H

#include <Arduino.h>
#include <WiFi.h>

class WifiNetworksList
{
public:
    static String get()
    {
        int foundNetworkCount = WiFi.scanNetworks();
        Serial.println("Near network scan completed");
        Serial.println(foundNetworkCount ? "Networks found" : "No WiFi Networks found");

        String foundNetworksHtml = "<ol>";

        foundNetworksHtml += "<li>";
        foundNetworksHtml += foundNetworkCount ? "Networks found" : "No WiFi Networks found";
        foundNetworksHtml += "</li>";


        for (int i = 0; i < foundNetworkCount; ++i)
        {
            foundNetworksHtml += "<li>";
            foundNetworksHtml += WiFi.SSID(i);
            foundNetworksHtml += " (";
            foundNetworksHtml += WiFi.RSSI(i);
            foundNetworksHtml += ")";
            foundNetworksHtml += (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*";
            foundNetworksHtml += "</li>";
        }

        foundNetworksHtml += "</ol>";

        return foundNetworksHtml;
    }
};

#endif // WIFINETWORKSLIST_H