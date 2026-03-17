#ifndef ESP_SMART_DASH_H
#define ESP_SMART_DASH_H

#pragma once
#include <Arduino.h>

#include "core/WiFiManager.h"
#include "core/ServerManager.h"

#include "widgets/ToggleWidget.h"
#include "widgets/SliderWidget.h"
#include "widgets/GaugeWidget.h"

#include "web/dashboard_html.h"
#include "web/dashboard_css.h"
#include "web/dashboard_js.h"
#include "web/api_routes.h"

#define SD_MAX_TOGGLES 15
#define SD_MAX_SLIDERS 10
#define SD_MAX_GAUGES 10

class ESPSmartDash {
public:
  ESPSmartDash();

  void begin(const char* ssid, const char* pass);

  void toggle(const String& name, int pin);
  void slider(const String& name, int pin);
  void gauge(const String& name, float* value);

  void handle();

private:
  SDWebServer server{80};

  ToggleWidget toggles[SD_MAX_TOGGLES];
  SliderWidget sliders[SD_MAX_SLIDERS];
  GaugeWidget gauges[SD_MAX_GAUGES];

  int tCount = 0;
  int sCount = 0;
  int gCount = 0;

  bool validPin(int p);

  void routeRoot();
  void routeJS();
  void routeCSS();

  void routeWidgets();
  void routeToggle();
  void routeSlider();
  void routeSensors();
};

#endif
