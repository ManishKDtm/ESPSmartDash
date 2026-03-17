#ifndef SD_WIFI_MANAGER_H
#define SD_WIFI_MANAGER_H

#pragma once
#include <Arduino.h>

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error "ESPSmartDash supports ESP32 and ESP8266 only"
#endif

class SDWiFiManager {
public:

  static void connect(const char* ssid, const char* pass) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
  }

  static IPAddress ip() {
    return WiFi.localIP();
  }
};

#endif
