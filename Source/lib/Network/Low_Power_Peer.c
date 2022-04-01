#include <WiFi.h>

// Hardcoded for now
const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

void WiFi_Init()
{
    // Station mode to connect to other networks
    WiFi.mode(WIFI_STA);

    // Attempt to connect to ssid with pass
    WiFi.begin(ssid, password);
    Serial.print("Connecting to wWiFi... ");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    // Display
    Serial.println();
    Serial.print(Wifi.localIP());
}

// Send the alert to the server
void Send_Alert()
{
    // IPAddress local_IP(192, 168, 1, 185);
    // IPAddress gateway(192, 168, 1, 1);
    // IPAddress subnet(255, 255, 0, 0);

    String serverName = "http://192.168.1.185:80/";

    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;

        http.begin(serverName.c_str());
        http.addHeader("Content-Type", "text/plain");

        // Send HTTP GET request
        int httpResponseCode = http.POST("alert");

        if (httpResponseCode > 0)
        {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            Serial.println(payload);
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
}