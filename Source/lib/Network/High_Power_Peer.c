// All peers
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

AsyncWebServer server(80);

String header;

String output26State = "off";
String output27State = "off";

const int output26 = 26;
const int output27 = 27;

void Server_Init()
{
    Serial.begin(115200);
    // Initialize the output variables as outputs
    pinMode(output26, OUTPUT);
    pinMode(output27, OUTPUT);
    // Set outputs to LOW
    digitalWrite(output26, LOW);
    digitalWrite(output27, LOW);

    // Starts the access point
    WiFi.softAP(ssid, password);

    // Some debugging
    Serial.println();
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    // Test route
    server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "hello world"); });

    server.begin();
}
