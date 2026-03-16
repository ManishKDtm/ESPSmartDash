#ifndef SD_SLIDER_WIDGET_H
#define SD_SLIDER_WIDGET_H

#pragma once
#include <Arduino.h>

class SliderWidget {

public:

  String name;
  int pin;
  int value;

  SliderWidget(){}

  SliderWidget(const String& n,int p){
    name=n;
    pin=p;
    value=0;
  }

};

#endif