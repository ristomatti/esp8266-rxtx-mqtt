# esp8266-rxtx-mqtt

ES8266 Serial to MQTT bridge.

## config.h template

```cpp
#ifndef CONFIG_H
#define CONFIG_H

const char* wifiSsid = "";
const char* wifiPassword = "";

const char* mqttHost = "";
const char* mqttClient = "";
const char* mqttUser = "";
const char* mqttPassword = "";

const char* statusTopic = "esp8266/status";
const char* rxTopic = "esp8266/rx";

#endif
```
