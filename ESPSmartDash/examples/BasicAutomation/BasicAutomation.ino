#include <ESPSmartDash.h>

ESPSmartDash dash;

void setup(){
Serial.begin(115200);
dash.begin("WiFi","Password");

dash.toggle("Light",5);
dash.toggle("Fan",18);

dash.slider("Brightness",19);

}

void loop(){
dash.handle();
}