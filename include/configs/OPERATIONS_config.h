#pragma once

#include <Arduino.h>

// Define accel behaviour
// #define HARDWARE_ACCEL
#define ACCEL_PGN 133512 // arbitrarily defined, but nothing exists on the market with this PGN yet
#define ACCEL_DELAY 100  // in ms, do 1000 / ACCEL_DELAY to get frequency, soo 100HZ

// Define GNSS behaious
// #define HARDWARE_GNSS
#define GNSS_PGN 129029        // according tp PGN specs
#define GNSS_COGSOG_PGN 129026 // according to PGN specs
#define GNSS_FREQ 1            // in Hz

// Define constants
#define THINGNAME "matts_esp32" // we no longer set this value automatically.
#define OTHER_THINGNAME "matts_other_esp32"
#include <configs/secrets/matts_esp32.h>

#ifndef ENVIRONMENT
#define ENVIRONMENT "UNKNOWN"
#endif
