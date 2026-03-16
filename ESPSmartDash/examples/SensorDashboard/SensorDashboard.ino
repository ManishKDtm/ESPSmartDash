#include <ESPSmartDash.h>

ESPSmartDash dash;

float temperature;

void setup(){
Serial.begin(115200);
dash.begin("WiFi","Password");

dash.toggle("Light",5);
dash.gauge("Temperature",&temperature);

}

void loop(){

temperature=random(20,35);

dash.handle();
}