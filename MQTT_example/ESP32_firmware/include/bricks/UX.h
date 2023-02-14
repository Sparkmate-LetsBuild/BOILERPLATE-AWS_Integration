#pragma once

// configs
#include <configs/HARDWARE_config.h>

// bricks

// libs
#include <Arduino.h>
#include <StatusLogger.h>

namespace UX
{
    bool button_state = false;

    /**
     * @brief Set the LED's state (as a bool, topic will be sent to later)
     *
     * @param state
     */
    void setLEDState(bool state)
    {
        digitalWrite(SYSTEM_UI_LED, state);
    }

    /**
     * @brief An interrupt-handled function to handle button interactions
     */
    void IRAM_ATTR button1Change()
    {
        button_state = !button_state;
    }

    void initUX()
    {
        // Initialize the User Interface
        pinMode(SYSTEM_UI_BUTTON_1, INPUT_PULLUP); // Pull the button pin high
        pinMode(SYSTEM_UI_LED, OUTPUT);            // Set the LED as an output
        attachInterrupt(SYSTEM_UI_BUTTON_1, button1Change, FALLING);
    }
}