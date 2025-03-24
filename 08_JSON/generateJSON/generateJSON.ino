#include <WiFi.h>
#include "time.h"
#include <ArduinoJson.h>

// 📡 Configura tu WiFi
const char* ssid       = "WLAN";
const char* password   = "testing1";

// 🌍 Cliente NTP
const char* ntpServer = "0.es.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

struct tm timeinfo;

// 📌 Configuración JSON
const char* sensor_name = "sensor_1";  
const int maxRegistros = 10;  // Máx. registros en JSON
StaticJsonDocument<512> doc;

void setup() {
    Serial.begin(115200);
    
    // 📡 Conectar a WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ WiFi conectado!");

    // 🌍 Iniciar cliente NTP
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
    time_t now = time(nullptr);
    Serial.printf("Unix Timestamp: %ld\n", now);


    // 📅 Obtener tiempo actual en UNIX y configurar JSON
    doc["bn"] = sensor_name;
    //doc["bt"] = now; // ⏳ Usar timestamp real
    doc.createNestedArray("e");
}

void loop() {
    JsonArray data = doc["e"].as<JsonArray>();

    // FIFO: eliminar el más antiguo si hay demasiados registros
    if (data.size() >= maxRegistros) {
        data.remove(0);
    }

    // 🔥 Obtener timestamp actualizado
    
    unsigned long tiempoActual = getLocalTime(&timeinfo);
    time_t now = time(nullptr);
    Serial.printf("Unix Timestamp: %ld\n", now);

    // 🌡️ Generar medición
    JsonObject medida = data.createNestedObject();
    medida["t"] = now; // Tiempo relativo
    medida["n"] = "temperature";
    medida["v"] = random(220, 250) / 10.0;  // Simular temperatura (22.0 - 25.0°C)
    medida["u"] = "Cel";

    // 🖨️ Imprimir JSON actualizado
    serializeJson(doc, Serial);
    Serial.println();

    delay(10000); // Esperar 10 segundos
}
