# esp8266-rxtx-mqtt

ES8266 Serial to MQTT bridge.

## config.h template

```cpp
#ifndef CONFIG_H
#define CONFIG_H

const int serialBaud = 19200;

const char* wifiSsid = "";
const char* wifiPassword = "";

const char* host = "";
const char* clientId = "";
const char* user = "";
const char* password = "";

const int timeout = 3000;
const boolean cleanSession = true;
const int keepAlive = 60;

const char* statusTopic = "esp8266/status";
const char* rxTopic = "esp8266/rx";

#endif
```
