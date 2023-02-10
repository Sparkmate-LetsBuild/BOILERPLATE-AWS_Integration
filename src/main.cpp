#include <bricks/MQTT_functions.h>
#include <bricks/UX.h>

void setup()
{
    MQTT_functions::setup();
    UX::initUX();
}

void loop()
{
    MQTT_functions::each_loop();
    delay(1000);
}