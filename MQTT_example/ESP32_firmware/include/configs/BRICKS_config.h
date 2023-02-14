#pragma once
#define BRICKS_config_h

namespace StatusLogger
{
    // -- EXAMPLE BRICKS LOGGER HANDLER
    const String NAME_UX = "UX";       // UX
    const String NAME_MQTT = "MQTT";   // Specific MQTT tasks (once this is connected, most statuses are with AWS specifically)
    const String NAME_AWS = "AWS";     // Interface with AWS
    const String NAME_ESP32 = "ESP32"; // specifically with the ESP32
}