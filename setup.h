#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <WiFi.h>
#include <FastLED.h>
#include "wificredentials.h"
#include "currentstate.h"

class Setup
{
    public:
        Setup();
        void run();
        CurrentState currentState();
    private:
        WiFiServer _server;
        bool _isResetMode;
        int _timeZone;
        String _foundNetworksHtml;
        void setupSerial();
        bool isResetMode();
        void reactToReset();
        void connectWifi(WifiCredentials credentials);
        void setupWifiCredentials();
        String htmlSSIDInputForm();
        void setupAP();
        void setupArduinoOTA();
        
};

#endif