#ifndef SD_TOGGLE_WIDGET_H
#define SD_TOGGLE_WIDGET_H

#pragma once
#include <Arduino.h>

class ToggleWidget {

public:

  String name;
  int pin;

  ToggleWidget(){}

  ToggleWidget(const String& n,int p){
    name=n;
    pin=p;
  }

};

#endif