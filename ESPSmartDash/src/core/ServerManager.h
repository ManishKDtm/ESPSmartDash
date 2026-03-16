#ifndef SD_SERVER_MANAGER_H
#define SD_SERVER_MANAGER_H
#pragma once
#include <Arduino.h>

#if defined(ESP32)
#include <WebServer.h>
typedef WebServer SDWebServer;
#elif defined(ESP8266)
#include <ESP8266WebServer.h>
typedef ESP8266WebServer SDWebServer;
#endif
#endif