#include "ESPSmartDash.h"

ESPSmartDash::ESPSmartDash(){
  tCount=sCount=gCount=0;
}

bool ESPSmartDash::validPin(int p){
  if(p>=6 && p<=11) return false;
  return true;
}

void ESPSmartDash::begin(const char* ssid,const char* pass){

  SDWiFiManager::connect(ssid,pass);

  Serial.print("Dashboard: http://");
  Serial.println(SDWiFiManager::ip());

  server.on(API_ROOT,[this](){routeRoot();});
  server.on(API_JS,[this](){routeJS();});
  server.on(API_CSS,[this](){routeCSS();});

  server.on(API_WIDGETS,[this](){routeWidgets();});
  server.on(API_CONTROL,[this](){routeToggle();});
  server.on(API_SLIDER,[this](){routeSlider();});
  server.on("/sensors",[this](){routeSensors();});
  server.begin();
}

void ESPSmartDash::toggle(const String& name,int pin){
  if(!validPin(pin)) return;
  pinMode(pin,OUTPUT);
  toggles[tCount++]=ToggleWidget(name,pin);
}

void ESPSmartDash::slider(const String& name,int pin){
  if(!validPin(pin)) return;
  pinMode(pin,OUTPUT);
  sliders[sCount++]=SliderWidget(name,pin);
}

void ESPSmartDash::gauge(const String& name,float* value){
  gauges[gCount++]=GaugeWidget(name,value);
}

void ESPSmartDash::routeSensors(){

  String json="{";

  for(int i=0;i<gCount;i++){

    json+="\""+gauges[i].name+"\":"+String(*gauges[i].value,2);

    if(i<gCount-1) json+=",";
  }

  json+="}";

  server.send(200,"application/json",json);
}

void ESPSmartDash::handle(){
  server.handleClient();
}

void ESPSmartDash::routeRoot(){
  server.send_P(200,"text/html",DASH_HTML);
}

void ESPSmartDash::routeJS(){
  server.send_P(200,"application/javascript",DASH_JS);
}

void ESPSmartDash::routeCSS(){
  server.send_P(200,"text/css",DASH_CSS);
}

void ESPSmartDash::routeWidgets(){

  String json="{\"toggles\":[";
  for(int i=0;i<tCount;i++){
    json+="{\"name\":\""+toggles[i].name+"\",\"pin\":"+String(toggles[i].pin)+"}";
    if(i<tCount-1) json+=",";
  }
  json+="],\"sliders\":[";

  for(int i=0;i<sCount;i++){
    json+="{\"name\":\""+sliders[i].name+"\",\"pin\":"+String(sliders[i].pin)+",\"value\":"+String(sliders[i].value)+"}";
    if(i<sCount-1) json+=",";
  }
  json+="],\"gauges\":[";

  for(int i=0;i<gCount;i++){
    json+="{\"name\":\""+gauges[i].name+"\",\"value\":"+String(*gauges[i].value,2)+"}";
    if(i<gCount-1) json+=",";
  }
  json+="]}";

  server.send(200,"application/json",json);
}

void ESPSmartDash::routeToggle(){
  int pin=server.arg("pin").toInt();
  digitalWrite(pin,!digitalRead(pin));
  server.send(200,"text/plain","OK");
}

void ESPSmartDash::routeSlider(){
  int pin=server.arg("pin").toInt();
  int val=server.arg("val").toInt();

#if defined(ESP32)
  ledcAttachPin(pin,0);
  ledcSetup(0,5000,8);
  ledcWrite(0,val);
#else
  analogWrite(pin,val);
#endif

  server.send(200,"text/plain","OK");
}