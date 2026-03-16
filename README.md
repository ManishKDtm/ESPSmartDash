ESPSmartDash is a simple and efficient Arduino library that generates a web-based dashboard directly from your ESP device.
With just a few lines of code, users can control GPIO pins, adjust PWM outputs, and visualize sensor data through an automatically generated interface.

The dashboard runs locally on the ESP device and requires no external server or cloud service, making it ideal for IoT projects, automation systems, and educational experiments.

Key Features

Automatic web dashboard generation

Toggle controls for GPIO devices

Slider controls for PWM outputs

Live sensor gauges with auto update

Lightweight and optimized for embedded systems

Compatible with ESP8266 and ESP32

Works directly in Arduino IDE

No cloud or external dependencies

Example Usage

#include <ESPSmartDash.h>

ESPSmartDash dash;

void setup() {

Serial.begin(115200);

dash.begin("WiFiName","WiFiPassword");

dash.toggle("Light",5);
dash.slider("Fan Speed",18);

}

void loop() {
dash.handle();
}

After uploading, open the ESP IP address in your browser to access the dashboard.

Ideal For

IoT beginners

Embedded systems students

Rapid prototyping

Home automation projects

Sensor monitoring dashboards