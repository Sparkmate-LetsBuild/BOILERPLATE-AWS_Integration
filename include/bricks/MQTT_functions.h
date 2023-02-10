#pragma once

// CONFIGS
#include "configs/HARDWARE_config.h"
#include "configs/OPERATIONS_config.h"

// BRICKS
#include <bricks/UX.h>

// LIBS
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
using namespace ArduinoJson; // Needed to make ArduinoJson compile 😡
#include "WiFi.h"

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PREFIX "$aws/things/"
#define AWS_IOT_PUBLISH_TOPIC "/shadow/update"
#define AWS_IOT_SUBSCRIBE_TOPIC "/shadow/update/delta"

enum MESSAGE_TYPE
{
    REPORTED,
    DESIRED
};

namespace MQTT_functions
{
    WiFiClientSecure net = WiFiClientSecure();
    MQTTClient client = MQTTClient(256);

    void publishMessage(bool state_to_send, MESSAGE_TYPE reported_desired)
    {
        DynamicJsonDocument doc(1000);
        JsonObject doc_status = doc.createNestedObject("state");
        String nest_payload = "reported";
        if (reported_desired == DESIRED) {
            nest_payload = "desired";
        }
        JsonObject doc_status_reported = doc_status.createNestedObject(nest_payload);
        doc_status_reported["status"] = state_to_send;

        char jsonBuffer[1024];
        serializeJson(doc, jsonBuffer); // print to client

        client.publish(String(AWS_IOT_PREFIX) + String(THINGNAME) + String(AWS_IOT_PUBLISH_TOPIC), jsonBuffer);
        // client.publish(AWS_IOT_STATES_TOPIC, jsonBuffer);
        Serial.print("Sending: ");
        Serial.println(jsonBuffer);
    }

    void messageHandler(String & topic, String & payload)
    {
        Serial.println("incoming: " + topic + " - " + payload);
        StaticJsonDocument<1024> sensor_doc;
        DeserializationError error_sensor = deserializeJson(sensor_doc, payload);
        Serial.println(payload);
        bool sensor = sensor_doc["state"]["status"];

        Serial.print("This light should now be: ");
        Serial.println(sensor);
        UX::setLEDState(sensor);
        publishMessage(sensor, REPORTED);
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
        client.subscribe(String(AWS_IOT_PREFIX) + String(THINGNAME) + String(AWS_IOT_SUBSCRIBE_TOPIC));

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
            publishMessage(state, DESIRED);
            prev_state = state;
            Serial.println("State set to " + String((state)));
        }
        client.loop();
    }
}