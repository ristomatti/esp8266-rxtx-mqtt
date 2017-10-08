#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <MQTTClient.h>
#include "config.h"

const uint16_t bufferSize = 250;

void setupMQTT();
void connect();

void messageReceived(String& topic, String& payload);

WiFiClientSecure wifiClient;
MQTTClient client;
EspClass esp;

void setup() {
  Serial.begin(115200);
  WiFi.begin(wifiSsid, wifiPassword);
  setupMQTT();
}

void loop() {
  client.loop();

  if (!client.connected()) {
    connect();
  }

  if (Serial.available()) {
    char buffer[bufferSize];
    Serial.readBytesUntil('\n', buffer, bufferSize);

    if (strlen(buffer) > 0) {
      StaticJsonBuffer<bufferSize> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(buffer);

      if (root.success()) {
        const char* topic = root["topic"].as<char*>();
        const char* payload = root["payload"].as<char*>();

        if (root.containsKey("retain") && root.containsKey("qos")) {
          const boolean retain = root["retain"].as<boolean>();
          const int qos = root["qos"].as<int>();
          client.publish(topic, payload, retain, qos);
        } else {
          client.publish(topic, payload);
        }
      }
    }

    memset(buffer, 0, sizeof(buffer));
  }
}

void messageReceived(String& topic, String& payload) {
  Serial.println(payload);
}

void setupMQTT() {
  client.begin(mqttHost, 8883, wifiClient);
  client.setOptions(50, true, 3000);
  client.setWill(statusTopic, "offline", 1, 1);
  client.onMessage(messageReceived);
}

void connect() {
  static unsigned int retryCount = 0;
  // Serial.print("Checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    if (retryCount > 10) {
      // Serial.println("\nRetry count exceeded 10, restarting...");
      esp.restart();
    }
    // Serial.print(".");
    delay(500);
  }

  // Serial.print("\nConnecting...");
  while (!client.connect(mqttClient, mqttUser, mqttPassword)) {
    // Serial.print(".");
    delay(500);
  }

  // Serial.println("\nConnected!");

  client.publish(statusTopic, "online", 1, 1);
  client.subscribe(rxTopic);
}
