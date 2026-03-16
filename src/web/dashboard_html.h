#pragma once
#include <Arduino.h>

const char DASH_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP SmartDash</title>
<link rel="stylesheet" href="/style.css">
</head>
<body>

<h2>ESP SmartDash</h2>
<div id="widgets" class="grid"></div>

<script src="/app.js"></script>
</body>
</html>
)rawliteral";