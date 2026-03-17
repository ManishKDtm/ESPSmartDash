#include "ESPSmartDash.h"

ESPSmartDash::ESPSmartDash() {
  tCount = 0;
  sCount = 0;
  gCount = 0;
}

bool ESPSmartDash::validPin(int p) {
  // Block flash pins on ESP8266 and ESP32
  if (p >= 6 && p <= 11) return false;

#if defined(ESP32)
  // Block input-only pins for output widgets
  if (p == 34 || p == 35 || p == 36 || p == 39) return false;
#endif

  return true;
}

void ESPSmartDash::begin(const char* ssid, const char* pass) {
  SDWiFiManager::connect(ssid, pass);

  Serial.print("Dashboard: http://");
  Serial.println(SDWiFiManager::ip());

  server.on(API_ROOT, [this]() { routeRoot(); });
  server.on(API_JS, [this]() { routeJS(); });
  server.on(API_CSS, [this]() { routeCSS(); });

  server.on(API_WIDGETS, [this]() { routeWidgets(); });
  server.on(API_CONTROL, [this]() { routeToggle(); });
  server.on(API_SLIDER, [this]() { routeSlider(); });
  server.on(API_SENSORS, [this]() { routeSensors(); });

  server.begin();
}

void ESPSmartDash::toggle(const String& name, int pin) {
  if (!validPin(pin)) return;
  if (tCount >= SD_MAX_TOGGLES) return;

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);

  toggles[tCount] = ToggleWidget(name, pin);
  tCount++;
}

void ESPSmartDash::slider(const String& name, int pin) {
  if (!validPin(pin)) return;
  if (sCount >= SD_MAX_SLIDERS) return;

  pinMode(pin, OUTPUT);

#if defined(ESP8266)
  analogWriteRange(255);
#endif

  sliders[sCount] = SliderWidget(name, pin);
  sCount++;
}

void ESPSmartDash::gauge(const String& name, float* value) {
  if (gCount >= SD_MAX_GAUGES) return;

  gauges[gCount] = GaugeWidget(name, value);
  gCount++;
}

void ESPSmartDash::routeSensors() {
  String json = "{";

  for (int i = 0; i < gCount; i++) {
    json += "\"" + gauges[i].name + "\":" + String(*gauges[i].value, 2);

    if (i < gCount - 1) json += ",";
  }

  json += "}";

  server.send(200, "application/json", json);
}

void ESPSmartDash::handle() {
  server.handleClient();
}

void ESPSmartDash::routeRoot() {
  server.send_P(200, "text/html", DASH_HTML);
}

void ESPSmartDash::routeJS() {
  server.send_P(200, "application/javascript", DASH_JS);
}

void ESPSmartDash::routeCSS() {
  server.send_P(200, "text/css", DASH_CSS);
}

void ESPSmartDash::routeWidgets() {
  String json = "{\"toggles\":[";

  for (int i = 0; i < tCount; i++) {
    json += "{\"name\":\"" + toggles[i].name + "\",\"pin\":" + String(toggles[i].pin) + "}";
    if (i < tCount - 1) json += ",";
  }

  json += "],\"sliders\":[";

  for (int i = 0; i < sCount; i++) {
    json += "{\"name\":\"" + sliders[i].name + "\",\"pin\":" + String(sliders[i].pin) +
            ",\"value\":" + String(sliders[i].value) + "}";
    if (i < sCount - 1) json += ",";
  }

  json += "],\"gauges\":[";

  for (int i = 0; i < gCount; i++) {
    json += "{\"name\":\"" + gauges[i].name + "\",\"value\":" + String(*gauges[i].value, 2) + "}";
    if (i < gCount - 1) json += ",";
  }

  json += "]}";

  server.send(200, "application/json", json);
}

void ESPSmartDash::routeToggle() {
  int pin = server.arg("pin").toInt();

  if (!validPin(pin)) {
    server.send(400, "text/plain", "Invalid pin");
    return;
  }

  digitalWrite(pin, !digitalRead(pin));
  server.send(200, "text/plain", "OK");
}

void ESPSmartDash::routeSlider() {
  int pin = server.arg("pin").toInt();
  int val = server.arg("val").toInt();

  if (!validPin(pin)) {
    server.send(400, "text/plain", "Invalid pin");
    return;
  }

  if (val < 0) val = 0;
  if (val > 255) val = 255;

  analogWrite(pin, val);

  for (int i = 0; i < sCount; i++) {
    if (sliders[i].pin == pin) {
      sliders[i].value = val;
      break;
    }
  }

  server.send(200, "text/plain", "OK");
}
