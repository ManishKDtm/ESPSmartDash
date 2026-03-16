#ifndef SD_GAUGE_WIDGET_H
#define SD_GAUGE_WIDGET_H

#pragma once
#include <Arduino.h>

class GaugeWidget {

public:

  String name;
  float* value;

  GaugeWidget(){}

  GaugeWidget(const String& n,float* v){
    name=n;
    value=v;
  }

};

#endif