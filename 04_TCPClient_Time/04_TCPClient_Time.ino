#include <WiFi.h>
#include "time.h"

const char* ssid       = "WLAN";
const char* password   = "testing1";
const char* serverIP = "192.168.6.208";    // Replace with the server IP address
const int serverPort = 12345;              // Replace with the server port

const char* ntpServer = "0.es.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

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
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  if (client.connected()) {
      client.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
      
  }
  
  delay(1000);
}
