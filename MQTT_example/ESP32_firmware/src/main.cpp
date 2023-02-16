// include Arduino.h first to avoid squiggles
#include <Arduino.h>

// configs
#include <configs/HARDWARE_config.h>
#include <configs/OPERATIONS_config.h>
#include <configs/BRICKS_config.h>

// bricks
#include <inits/firmware_details_init.h>
#include <bricks/MQTT_functions.h>
#include <bricks/UX.h>

void setup()
{
    // Begin core systems
    Serial.begin(SERIAL_MON_BAUD);
    UX::initUX();

    // Begin firmware reporting
    Firmware::init();

    // Setup the core MQTT operations
    MQTT_functions::setup();
}

void loop()
{

    // Setup the board for normal operations -- These are verbosely ordered tasks
    MQTT_functions::eachLoop(UX::button_state);
    delay(200);
}