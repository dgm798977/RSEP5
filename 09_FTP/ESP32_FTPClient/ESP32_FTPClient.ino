#include <WiFi.h>
#include <WiFiClient.h>    
#include "ESP32_FTPClient.h"
#include "octocat.h"
#include "time.h"
#include <ArduinoJson.h>

const char* ssid       = "WLAN";
const char* password   = "testing1";

// 🌍 Cliente NTP
const char* ntpServer = "0.es.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;

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

char ftp_server[] = "192.168.171.35";
char ftp_user[]   = "test";
char ftp_pass[]   = "test1";

char working_dir[]   = ".";
char jsonBuffer[1024];

ESP32_FTPClient ftp (ftp_server,ftp_user,ftp_pass, 5000, 2);


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.println("Connecting Wifi...");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
      
  }
  Serial.println("IP address: ");
      
  Serial.println(WiFi.localIP());

  // 🌍 Iniciar cliente NTP
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
    time_t now = time(nullptr);
    Serial.printf("Unix Timestamp: %ld\n", now);


    // 📅 Obtener tiempo actual en UNIX y configurar JSON
    doc["bn"] = sensor_name;
    //doc["bt"] = now; // ⏳ Usar timestamp real
    doc.createNestedArray("e");

  ftp.OpenConnection();

  // Create the new image file and send the image
  ftp.ChangeWorkDir(working_dir);
  


  for (int i = 0; i < 10; i++) {
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
    serializeJson(doc, jsonBuffer);
    Serial.println();

    delay(10000); // Esperar
  }
  char filename[50];
  snprintf(filename, sizeof(filename), "data_%04d-%02d-%02d_%02d-%02d-%02d.json",
             timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
             timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  ftp.InitFile("Type A");
  ftp.NewFile(filename); // Nombre del archivo en el servidor
  ftp.Write(jsonBuffer);
  ftp.CloseFile();
}

void loop() {
  delay(1000);
}
