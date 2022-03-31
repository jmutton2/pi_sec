#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define KEYPAD
//#define DOOR_SENSOR
// Define other nodes to be made

#ifdef KEYPAD
#include <Touch.h>
#endif

#ifdef DOOR_SENSOR

#endif

// Replace with your network credentials
const char *ssid = "REPLACE_WITH_YOUR_SSID";
const char *password = "REPLACE_WITH_YOUR_PASSWORD";

const char *PARAM_INPUT_1 = "output";
const char *PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ECE3375 Home Security!</h2>
</body>W
</html>
)rawliteral";

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(33, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(33, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html, processor); });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK"); });

  // Start server
  server.begin();

  // To run once

  // ------------------------------- \\
  // Define network SSID and PASS
  // Define GPIO pins to read from

  // if (keypad)
  // Run Set_Pass()
}

void loop()
{
  // To run repetedly

  // if (keypad)
  // ------------------------------- \\
    // Check for Add_Node()
  // > Make a connection

  // Check for Enabl_Sys()
  // > Set a flag to enable some stuff
  // > Send sys_flag to all peers

  // Check for Disable_Sys()
  // > Set a flag to not check stuff
  // > Send sys_flag to all peers

  // Check for Remove_Node()
  // > Check for close packet
  // > Send close packet
  // > Close the connection that sent close packet

  // if (door_sensor)
  // Make connection

  // Check Flag_Change()
  // > Set sys_flag if flag changed values << THIS IS FLAG

  // Check Door_State_Changed()
  // > Send door_sensor_flag through sock

  // Check for Close_Connection()
  // > Send a request to close packet
  // > Await response and close if close packet received
}