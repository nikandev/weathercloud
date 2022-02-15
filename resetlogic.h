#ifndef RESETLOGIC_H
#define RESETLOGIC_H

#include <Arduino.h>
#include "abstractlogic.h"
#include <WiFi.h>

class ResetLogic : public AbstractLogic
{
    public:
        ResetLogic();
        void run() override;
    private:
        WiFiServer* _server;
        void processClientRequest(WiFiClient& client);
};

#endif // RESETLOGIC_H
