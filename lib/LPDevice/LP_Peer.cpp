#include <WiFi.h>
#include <ArduinoHttpClient.h>

// Hardcoded for now
const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

char serverAddress[] = "192.168.4.1";
int port = 80;

void WiFi_Init()
{
    Serial.begin(115200);

    Serial.print("Attempting to make connection");
    // Station mode to connect to other networks
    WiFi.mode(WIFI_STA);

    // Attempt to connect to ssid with pass
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi... ");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    // Display
    Serial.println();
    Serial.print(WiFi.localIP());
}

// Send the alert to the server
void Send_Alert()
{
    // Check WiFi connection status
    if (WiFi.status() == 3)
    {

        WiFiClient wifi;
        HttpClient client = HttpClient(wifi, serverAddress, port);

        client.get("/alert");

        // Get response
        int statusCode = client.responseStatusCode();
        String response = client.responseBody();

        if (statusCode > 0)
        {
            Serial.print("HTTP Response code: ");
            Serial.println(statusCode);
            Serial.println(response);
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(statusCode);
        }

        client.stop();
    }
    else
    {
        Serial.println("WiFi Not Connected");
    }
}