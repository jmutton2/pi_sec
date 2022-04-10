// All HP peers

// Note >> This needs to connect to other peers
// May use MAC address for wifi-less connections

#define ALERT_INTERRUPT 27

#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <stdio.h>

const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

AsyncWebServer server(80);

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
                digitalWrite(27, HIGH); });

  server.begin();
}

/*/------------------------------------\*\
| |----------FUTURE-EXPANSION----------| |
\ \------------------------------------/ /

Create peer to peer socket connections among peers
Use of kademlia to store and manage peers

Check for Remove_Node()
> Check for close packet
> Send close packet
> Close the connection that sent close packet


// Note >> Mem system state will need to change based on peers
void HP_Device_Loop(Control mem)
{
    if (mem->system_state == 2)
    {
    }

    if (mem->system_state == 3)
    {
    }
    //#STATE: ARMED
    // Check for UNARM interrupt
    // Check for AWAIT_ALARM interrupt

    //#STATE: UNARMED
    // Check for ARM interrupt
}
*/