#include <WiFi.h>
#include "time.h"

const char* ssid = "WLAN";            // Replace with your Wi-Fi SSID
const char* password = "testing1";    // Replace with your Wi-Fi password
const char* serverIP = "192.168.171.35";    // Replace with the server IP address
const int serverPort = 81;              // Replace with the server port

const char* ntpServer = "0.es.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;
bool active = true;
String message = "";
WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi!");
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  

  // Try to connect to the server
  Serial.print("Connecting to server: ");
  Serial.print(serverIP);
  Serial.print(":");
  Serial.println(serverPort);

  if (!client.connect(serverIP, serverPort)) {
    Serial.println("Connection failed!");
    return;
  }

  Serial.println("Connected to server!");
  client.println("Hello from ESP32 client!");  // Send initial message to the server
}

void loop() {
  delay(1000);
  if(active){
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
      return;
    }
    if (client.connected()) {
        client.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
        
    }
  }
  if (client.available()) {
        // Read data from the client (your phone)
        message = client.readStringUntil('\n');
        message.trim();
        Serial.println("Message from client: " + message);
  }
  if (message == "start") {
    active = true;
  }
  if (message == "stop") {
    active = false;
    Serial.println("Ive said stop");
  }
  
}