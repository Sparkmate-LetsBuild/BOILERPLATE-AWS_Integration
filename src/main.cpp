#include "MQTT_functions.h"

void setup()
{
    MQTT_functions::setup();
}

void loop()
{
    MQTT_functions::each_loop();
    delay(1000);
}