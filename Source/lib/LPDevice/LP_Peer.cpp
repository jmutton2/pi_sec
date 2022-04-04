#include <WiFi.h>
#include <ArduinoHttpClient.h>

// Hardcoded for now
const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

// Hard coded for now
String serverName = "http://192.168.1.185:80/alert";

char serverAddress[] = "192.168.1.185";
int port = 80;

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
    Serial.print(WiFi.localIP());
}

// Send the alert to the server
void Send_Alert()
{

    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {

        WiFiClient wifi;
        HttpClient client = HttpClient(wifi, serverAddress, port);

        // Define content type and message
        String contentType = "text/plain";
        String postData = "alert from {peer}";

        client.post("/alert", contentType, postData);

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