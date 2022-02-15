#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <WiFi.h>
#include "wificredentials.h"
#include "abstractlogic.h"
#include "mainlogic.h"
#include "resetlogic.h"

class Setup
{
    public:
        Setup();
        void run();
        AbstractLogic* result();
    private:
        AbstractLogic* _result;
        bool _isResetMode;
        int _timeZone;
        void setupSerial();
        bool isResetMode();
        void setupAP();
        void processReset();
        void processMain();
        void connectWifi(WifiCredentials credentials);
        void setupWifiCredentials();
        void setupArduinoOTA();
};

#endif
