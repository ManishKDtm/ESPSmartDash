#pragma once
#include <Arduino.h>

const char DASH_CSS[] PROGMEM = R"rawliteral(

body{
  font-family: Arial;
  background: #f4f4f4;
  text-align: center;
  margin: 0;
}

h2{
  background: #333;
  color: #fff;
  padding: 12px;
  margin: 0;
}

.grid{
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  padding: 10px;
}

.card{
  background: #ffffff;
  border-radius: 10px;
  padding: 15px;
  margin: 10px;
  min-width: 180px;
  box-shadow: 0 2px 6px rgba(0,0,0,0.2);
}

button{
  padding: 10px 16px;
  font-size: 16px;
  cursor: pointer;
}

input[type=range]{
  width: 160px;
}

.gauge{
  font-size: 28px;
  font-weight: bold;
  margin-top: 6px;
}

)rawliteral";