// All peers
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <stdio.h>

const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

AsyncWebServer server(80);

// String header;
// String output27State = "off";

const int ALERT_INTERRUPT = 27;

void Server_Init()
{
    Serial.begin(115200);

    // Define interrupt pin
    pinMode(ALERT_INTERRUPT, OUTPUT);
    digitalWrite(ALERT_INTERRUPT, LOW);

    // Starts the access point
    WiFi.softAP(ssid, password);

    // Some debugging
    Serial.println();
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    // Test route
    server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hello World"); });

    server.on("/end", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "end"); });

    server.on("/alert", HTTP_POST, [](AsyncWebServerRequest *request)
              {
                request->send(200, "text/plain", "Message Received");    
                digitalWrite(ALERT_INTERRUPT, HIGH); });

    server.begin();
}
