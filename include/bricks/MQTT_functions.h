#pragma once

// CONFIGS
#include "configs/HARDWARE_config.h"
#include "configs/OPERATIONS_config.h"

// LIBS
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
using namespace ArduinoJson; // Needed to make ArduinoJson compile 😡
#include "WiFi.h"

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

namespace MQTT_functions
{
    WiFiClientSecure net = WiFiClientSecure();
    MQTTClient client = MQTTClient(256);

    void publishMessage(bool state_to_send)
    {
        DynamicJsonDocument doc(1000);
        doc["time"] = millis();
        doc["sensor_id"] = THINGNAME;
        JsonObject doc_request = doc.createNestedObject("request");
        doc_request["device"] = OTHER_THINGNAME;
        doc_request["state"] = state_to_send;

        char jsonBuffer[1024];
        serializeJson(doc, jsonBuffer); // print to client

        client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
        Serial.println("Message sent...");
    }

    void messageHandler(String &topic, String &payload)
    {
        Serial.println("incoming: " + topic + " - " + payload);

        StaticJsonDocument<200> doc;
        deserializeJson(doc, payload);
        const char *message = doc["message"];
        Serial.println(message);
        // const char *message = doc["message"];
    }

    void connectAWS()
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        Serial.println("Connecting to Wi-Fi");

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        Serial.println("");

        // Configure WiFiClientSecure to use the AWS IoT device credentials
        net.setCACert(AWS_CERT_CA);
        net.setCertificate(AWS_CERT_CRT);
        net.setPrivateKey(AWS_CERT_PRIVATE);

        // Connect to the MQTT broker on the AWS endpoint we defined earlier
        client.begin(AWS_IOT_ENDPOINT, 8883, net);

        // Create a message handler
        client.onMessage(messageHandler);

        Serial.print("Connecting to AWS IOT");

        while (!client.connect(THINGNAME))
        {
            Serial.print(".");
            delay(100);
        }

        if (!client.connected())
        {
            Serial.println("AWS IoT Timeout!");
            return;
        }

        // Subscribe to a topic
        client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

        Serial.println("");

        Serial.println("AWS IoT Connected!");
    }

    void setup()
    {
        Serial.begin(Serial_Mon_Baud);
        connectAWS();
    }

    bool prev_state = false;
    void each_loop(bool state)
    {
        if (prev_state != state)
        {
            publishMessage(state);
            prev_state = state;
        }
        client.loop();
    }
}