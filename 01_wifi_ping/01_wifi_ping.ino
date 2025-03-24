#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Ping.h>

// Credenciales de la red WiFi
const char* ssid = "WLAN";
const char* password = "testing1";
const IPAddress remote_ip(8, 8, 8, 8);

void setup() {
    Serial.begin(115200);  
    WiFi.begin(ssid, password);  

    Serial.print("Conectando a WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConectado a la red WiFi");
    Serial.print("Dirección IP asignada: ");
    Serial.println(WiFi.localIP());  // Imprime la IP asignada al ESP32

    Serial.print("Pinging ip ");
  Serial.println(remote_ip);

  if(Ping.ping(remote_ip)) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }
  
}

void loop() {
    // No es necesario nada aquí
}

