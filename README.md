# 🧪 Laboratory Practices - Practice 5 - Redes de sensores electrónicos

This repository contains the fifth laboratory practice for the **Redes de sensores electrónicos** course. Each section is organized in its own folder and includes the necessary files along with a brief description.
In this practice, we will be testing different internet protocols, managing local IP addresses and platforms. Everything will be set up using WiFi connection on an ESP32.

## 📖 Section Overview

### 📁 Section 1 - 01_wifi_ping
📌 Simple Arduino Script to check WiFi connection and ping to Google servers.  
📄 Main files:  
- `01_wifi_ping.ino`: Connects to WiFi and checks if ping  with server is received.

### 📁 Section 2 - 02_ntpTime
📌 Obtains current time from NTP server and prints local time each second.
📄 Main files:  
- `02_ntpTime.ino`: Prints local time each second by previously connecting via WiFi to an NTP server in order to syncronize time.

### 📁 Section 3 - 03_TCPServer
📌 Sets up a TCP chat between your phone and the ESP32. 
📄 Main files:  
- `03_TCPServer.ino`: chat using a TCP Android chat app and the Serial Monitor of the ESP32 on Arduino IDE.

### 📁 Section 4 - 04_TCPClient_Time
📌 Mix of Sections 2 & 3. Sending time through TCP by previously obtaining syncronized time from NTP server. 
📄 Main files:  
- `04_TCPClient_Time.ino`: each second time gets sent through FTP.

### 📁 Section 5 - 05_TCPClient_Time_StartStop
📌 Modifies behavior of last section by adding command from 3rd device to stop sending time. 
📄 Main files:  
- `05_TCPClient_Time_StartStop.ino`: adds new functionality by adding option to stop from sending Time by using command "stop".

### 📁 Section 6 - 06_PythonTCPServer&Client
📌 Uses code from last section to send data from ESP32 to PC running Python Script. 
📄 Main files:  
- `TCPServer.py`: receives data from ESP32 using TCP.
- `clientTime.ino`: sends data to PC through TCP.

### 📁 Section 7 - 07_htmlServer
📌 Creates a server on the ESP32 that you can use to access website to control events. 
📄 Main files:  
- `esp32Server.ino`: Server on Arduino.

### 📁 Section 8 - 08_JSON
📌 Creates JSON file using correct format. 
📄 Main files:  
- `generateJSON.ino`: With data, it generates a JSON file each 10 seconds.

### 📁 Section 9 - 09_FTP
📌 Using fileZilla on the other end, we test functionality of sending files using FTP protocol. 
📄 Main files:  
- `ESP32_FTPClient.ino`: Sends file using FTP.

### 📁 Section 10 - 10_MQTT
📌 Using MQTT protocol to see its capabilities. 
📄 Main files:  
- `publish.ino`: working code from example as publisher of an increasing number.
- `subscribe.ino`: working code from example as subscribed of a topic that gets updated each time a publisher posts sth.


