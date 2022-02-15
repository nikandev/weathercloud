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
                    "<p style=\"text-align: center;\"><input type=\"submit\" value=\"Сохранить\" /></p>"
                "<form>"
                "</html>"
                "\r\n";

                return htmlPage;
        }

        static String currentWeatherInterface()
        {
                String htmlPage =
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html; charset=utf-8\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "<!DOCTYPE HTML>"
                    "<html>"
                    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">" +
                    svgSun() +
                    svgCloud() +
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
                    "<p style=\"text-align: center;\"><input type=\"submit\" value=\"Сохранить\" /></p>"
                "<form>"
                "</html>"
                "\r\n";

                return htmlPage;
        }

private:
        static String svgSun()
        {
                String s =
                    "<svg"
                    "width=\"74.247475mm\""
                    "height=\"74.247475mm\""
                    "viewBox=\"0 0 74.247476 74.247473\""
                    "version=\"1.1\""
                    "id=\"svg5\""
                    "inkscape:version=\"1.1.1 (3bf5ae0d25, 2021-09-20)\""
                    "sodipodi:docname=\"svgSun.svg\""
                    "xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\""
                    "xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\""
                    "xmlns=\"http://www.w3.org/2000/svg\""
                    "xmlns:svg=\"http://www.w3.org/2000/svg\">"
                    "<sodipodi:namedview"
                    "id=\"namedview7\""
                    "pagecolor=\"#505050\""
                    "bordercolor=\"#ffffff\""
                    "borderopacity=\"1\""
                    "inkscape:pageshadow=\"0\""
                    "inkscape:pageopacity=\"0\""
                    "inkscape:pagecheckerboard=\"1\""
                    "inkscape:document-units=\"mm\""
                    "showgrid=\"false\""
                    "fit-margin-top=\"1\""
                    "fit-margin-left=\"1\""
                    "fit-margin-right=\"1\""
                    "fit-margin-bottom=\"1\""
                    "inkscape:zoom=\"0.77771465\""
                    "inkscape:cx=\"-110.5804\""
                    "inkscape:cy=\"-82.935303\""
                    "inkscape:window-width=\"2560\""
                    "inkscape:window-height=\"1369\""
                    "inkscape:window-x=\"1912\""
                    "inkscape:window-y=\"-8\""
                    "inkscape:window-maximized=\"1\""
                    "inkscape:current-layer=\"layer1\" />"
                    "<defs"
                    "id=\"defs2\" />"
                    "<g"
                    "inkscape:label=\"Слой 1\""
                    "inkscape:groupmode=\"layer\""
                    "id=\"layer1\""
                    "transform=\"translate(-66.21658,-145.60814)\">"
                    "<circle"
                    "style=\"fill:#ffffff;stroke:#000000;stroke-width:2.165\""
                    "id=\"path1387\""
                    "cx=\"103.34032\""
                    "cy=\"182.73187\""
                    "r=\"35.041237\" />"
                    "</g>"
                    "</svg>";

                    return s;
        }

        static String svgCloud()
        {
                String s =
                    "<svg"
                    "width=\"166.44347mm\""
                    "height=\"101.34046mm\""
                    "viewBox=\"0 0 166.44347 101.34046\""
                    "version=\"1.1\""
                    "id=\"svg5\""
                    "inkscape:version=\"1.1.1 (3bf5ae0d25, 2021-09-20)\""
                    "sodipodi:docname=\"svgCloud.svg\""
                    "xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\""
                    "xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\""
                    "xmlns=\"http://www.w3.org/2000/svg\""
                    "xmlns:svg=\"http://www.w3.org/2000/svg\">"
                    "<sodipodi:namedview"
                    "id=\"namedview7\""
                    "pagecolor=\"#505050\""
                    "bordercolor=\"#ffffff\""
                    "borderopacity=\"1\""
                    "inkscape:pageshadow=\"0\""
                    "inkscape:pageopacity=\"0\""
                    "inkscape:pagecheckerboard=\"1\""
                    "inkscape:document-units=\"mm\""
                    "showgrid=\"false\""
                    "fit-margin-top=\"1\""
                    "fit-margin-left=\"1\""
                    "fit-margin-right=\"1\""
                    "fit-margin-bottom=\"1\""
                    "inkscape:zoom=\"0.77771465\""
                    "inkscape:cx=\"73.291663\""
                    "inkscape:cy=\"-22.501826\""
                    "inkscape:window-width=\"2560\""
                    "inkscape:window-height=\"1369\""
                    "inkscape:window-x=\"1912\""
                    "inkscape:window-y=\"-8\""
                    "inkscape:window-maximized=\"1\""
                    "inkscape:current-layer=\"layer1\" />"
                    "<defs"
                    "id=\"defs2\" />"
                    "<g"
                    "inkscape:label=\"Слой 1\""
                    "inkscape:groupmode=\"layer\""
                    "id=\"layer1\""
                    "transform=\"translate(-17.608363,-129.65971)\">"
                    "<path"
                    "id=\"path951\""
                    "style=\"fill:#ffffff;stroke:#000000;stroke-width:2.165\""
                    "d=\"m 93.175267,131.74221 a 48.525707,48.525707 0 0 0 -43.368928,26.80663 35.381443,35.381443 0 0 0 -30.115476,34.98701 35.381443,35.381443 0 0 0 35.381303,35.38182 35.381443,35.381443 0 0 0 17.596342,-4.69015 48.525707,48.525707 0 0 0 20.506759,4.56613 48.525707,48.525707 0 0 0 27.209713,-8.35298 37.762886,37.762886 0 0 0 23.82128,8.477 37.762886,37.762886 0 0 0 37.76307,-37.76307 37.762886,37.762886 0 0 0 -22.52627,-34.55086 24.83505,24.83505 0 0 0 -24.76232,-22.94382 24.83505,24.83505 0 0 0 -15.6409,5.55211 48.525707,48.525707 0 0 0 -25.864573,-7.46982 z\" />"
                    "</g>"
                    "</svg>";
        }
};

#endif
