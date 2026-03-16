# ESPSmartDash

![Arduino](https://img.shields.io/badge/Arduino-Compatible-green)
![PlatformIO](https://img.shields.io/badge/PlatformIO-Compatible-blue)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

**ESPSmartDash** is a lightweight Arduino library that automatically generates a responsive web dashboard for ESP devices.  
It allows students and hobbyists to **control GPIO devices and monitor sensors** directly in a web browser without any cloud dependency.

---

## Features

- Automatic web dashboard generation  
- Toggle controls for digital devices (LEDs, relays, buzzers)  
- Slider controls for PWM outputs (motors, LED brightness)  
- Live sensor gauges with real-time auto-update  
- Lightweight and optimized for ESP8266/ESP32  
- Fully offline, no cloud or external server required  
- Simple API: just define toggles, sliders, and gauges  
- Works in Arduino IDE and PlatformIO  

---

## Supported Hardware

- **ESP32**  
- **ESP8266**  

---

## Installation

### Arduino Library Manager

1. Open **Arduino IDE**  
2. Go to **Sketch → Include Library → Manage Libraries…**  
3. Search for **ESPSmartDash**  
4. Click **Install**  

### Manual Installation

1. Download the repository ZIP  
2. Extract it to your Arduino libraries folder:

```text
Documents/Arduino/libraries/

```
## **Basic Example **
```text
#include <ESPSmartDash.h>

ESPSmartDash dash;

float temperature = 25.0;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi and start dashboard
  dash.begin("WiFiSSID", "WiFiPassword");

  // Add toggle, slider, and gauge
  dash.toggle("Light", 5);
  dash.slider("Fan", 18);
  dash.gauge("Temperature", &temperature);
}

void loop() {
  dash.handle();  // Handle web server requests
}

```

