// All HP peers

// Note >> This needs to connect to other peers
// May use MAC address for wifi-less connections

#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <stdio.h>

const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

AsyncWebServer server(80);

const int ALERT_INTERRUPT = 27;

// Set permanent IP address << Until we discover method to connect dynamically and make requests
IPAddress local_IP(192, 168, 1, 185);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

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

  // Trigger an alert
  server.on("/alert", HTTP_GET, [](AsyncWebServerRequest *request)
            {
                request->send(200, "text/plain", "Message Received");    
                digitalWrite(ALERT_INTERRUPT, HIGH); });

  server.begin();
}

/*/------------------------------------\*\
| |----------FUTURE-EXPANSION----------| |
\ \------------------------------------/ /

Will connect to a local wifi network
Create peer to peer socket connections among peers
Use of kademlia to store and manage peers

// Check for Remove_Node()
// > Check for close packet
// > Send close packet
// > Close the connection that sent close packet

*/
