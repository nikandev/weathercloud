#ifndef HTML_H
#define HTML_H

#include <Arduino.h>
#include "weatherdata.h"

class Html
{
public:
    static String credentialsInputForm()
    {
        String htmlPage =
                         "HTTP/1.1 200 OK\r\n"
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
    String currentWeatherInterface(const Weather& w)
    {
            // Todo: Страница с погодой, реализовать, использовать
    }
};

#endif
