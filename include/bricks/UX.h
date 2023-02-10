#pragma once

// configs
#include <configs/HARDWARE_config.h>

// bricks
#include <bricks/status_logger.h>

// libs
#include <Arduino.h>

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
        button_state = state;
        digitalWrite(SYSTEM_UI_LED, state);
        Serial.println("State set to " + (state) ? "HIGH" : "LOW");
    }

    /**
     * @brief An interrupt-handled function to handle button interactions (and pipe to handlebutton)
     */
    void IRAM_ATTR button1Change()
    {
        setLEDState(digitalRead(SYSTEM_UI_BUTTON_1));
    }

    void initUX()
    {
        // Initialize the User Interface
        pinMode(SYSTEM_UI_BUTTON_1, INPUT_PULLUP); // Pull the button pin high
        attachInterrupt(SYSTEM_UI_BUTTON_1, button1Change, CHANGE);
        pinMode(SYSTEM_UI_LED, OUTPUT); // Pull the button pin high
    }
}