#include <WiFi.h>

const char* ssid = "WLAN";            // Replace with your Wi-Fi SSID
const char* password = "testing1";    // Replace with your Wi-Fi password
WiFiServer server(12345);                  // Server will listen on port 12345

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

  Serial.print("Dirección IP asignada: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("TCP Server started on port 12345");
}

void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {
    Serial.println("New client connected");

    // Send a greeting message
    client.println("Welcome to the ESP32 TCP server!");

    // Chat loop
    while (client.connected()) {
      if (client.available()) {
        // Read data from the client (your phone)
        String message = client.readStringUntil('\n');
        Serial.println("Message from client: " + message);
        
      
      }
      if (Serial.available()) {
        String serialInput = Serial.readStringUntil('\n');
        
        // Send the message typed in Serial Monitor to the connected client
        if (client.connected()) {
          client.println("Message from server: " + serialInput);
          Serial.println("Sent to client: " + serialInput);
        }
      }
    }
    // Client disconnected
    Serial.println("Client disconnected");
    client.stop();
  }
}
