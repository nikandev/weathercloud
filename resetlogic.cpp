#include "resetlogic.h"
#include "html.h"

ResetLogic::ResetLogic() 
    : _server(new WiFiServer(80))
{
}

void ResetLogic::run()
{
    WiFiClient client = _server->available();
    processClientRequest(client);
}

void ResetLogic::processClientRequest(WiFiClient& client)
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
                    String html = Html::credentialsInputForm();
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
