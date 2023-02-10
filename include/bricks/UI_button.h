#pragma once

// configs
#include <configs/HARDWARE_config.h>

// bricks
#include <bricks/status_logger.h>

// libs
#include <Arduino.h>

namespace UI_Buttons
{
    unsigned long button1DepressedTime = 0;
    // unsigned long button2DepressedTime = 0;

    typedef int ACTION_TIME;                    // ... for anything over 10s we ignore it, it's likely the button was leaned against
    const ACTION_TIME UI_B_ota = 10000;         // For anything up to 10s we restart in OTA mode until restarting again
    const ACTION_TIME UI_B_reset = 4000;        // For anything up to 4s, reset the system
    const ACTION_TIME UI_B_system_check = 1000; // For anything up to 1s we log a system check to console + logs
    const ACTION_TIME UI_B_ignore = 200;        // For anything less than 200ms, just ignore, it's likely a knock
    void handleButton1(int time);
    void IRAM_ATTR button1Change();
    // void handleButton2(int time);
    // void IRAM_ATTR button2Change();

    void initSwitchesAndButtons()
    {
        // Initialize the User Interface
        pinMode(SYSTEM_UI_BUTTON_1, INPUT_PULLUP); // Pull the button pin high
        attachInterrupt(SYSTEM_UI_BUTTON_1, UI_Buttons::button1Change, CHANGE);
        // pinMode(SYSTEM_UI_BUTTON_2, INPUT_PULLDOWN); // Pull the button pin high
        // attachInterrupt(SYSTEM_UI_BUTTON_2, UI_Buttons::button2Change, CHANGE);
        pinMode(SYSTEM_UI_SWITCH, INPUT); // Pull the button pin high
    }

    /**
     * @brief Is the switch high or low? - Used for 4G enabling/disabling
     *
     * @returns true if high, otherwise false
     */
    bool switchActive()
    {
        return digitalRead(SYSTEM_UI_SWITCH);
    }

    /**
     * @brief An interrupt-handled function to handle button interactions (and pipe to handlebutton)
     */
    void IRAM_ATTR button1Change()
    {
        if (millis() - button1DepressedTime <= UI_B_ignore)
        {
            return;
        }
        if (!digitalRead(SYSTEM_UI_BUTTON_1))
        // Button DOWN
        {
            button1DepressedTime = millis(); // set the time to now
        }
        else
        // Button UP
        {
            handleButton1(millis() - button1DepressedTime);
            button1DepressedTime = 0; // release the timer for use again later
        }
    }

    /**
     * @brief Decide what to do now that the button has been pressed for some notable time
     *
     * @param time The duration that the button was pressed for (see ACTION_TIMEs above).
     */
    void handleButton1(int time)
    {
        StatusLogger::log(0, StatusLogger::NAME_SIMCOM, "Button 1 was pressed for " + String(time) + "secs.");
        if (time <= UI_B_system_check)
        {
            // retrieve and report systems values
            StatusLogger::printSessionDetails();
            StatusLogger::printBrickStatuses();
        }
        else if (time <= UI_B_reset)
        {
            // reset the system
        }
        else if (time <= UI_B_ota)
        {
            // set the system mode to OTA and restart the module, TODO: Matt
        }
        else
        {
            // do nothing, it's likely the button was leaned on..
            return;
        }
    }

    // /**
    //  * @brief An interrupt-handled function to handle button interactions (and pipe to handlebutton)
    //  */
    // void IRAM_ATTR button2Change()
    // {
    //     if (millis() - button2DepressedTime <= UI_B_ignore)
    //     {
    //         return;
    //     }
    //     if (digitalRead(SYSTEM_UI_BUTTON_2))
    //     // Button DOWN
    //     {
    //         button2DepressedTime = millis(); // set the time to now
    //     }
    //     else
    //     // Button UP
    //     {
    //         handleButton2(millis() - button2DepressedTime);
    //         button2DepressedTime = 0; // release the timer for use again later
    //     }
    // }

    // /**
    //  * @brief Decide what to do now that the button has been pressed for some notable time
    //  *
    //  * @param time The duration that the button was pressed for (see ACTION_TIMEs above).
    //  */
    // void handleButton2(int time)
    // {
    //     StatusLogger::log(0, StatusLogger::NAME_SIMCOM, "Button 2 was pressed for " + String(time) + " but haven't assigned anything to this button yet!");
    // }
}