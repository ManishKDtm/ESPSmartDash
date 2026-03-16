#ifndef SD_WIFI_MANAGER_H
#define SD_WIFI_MANAGER_H
#pragma once
#include <Arduino.h>

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

class SDWiFiManager {

public:

static void connect(const char* ssid,const char* pass){

WiFi.begin(ssid,pass);

while(WiFi.status()!=WL_CONNECTED){
delay(500);
}

}

};
#endif