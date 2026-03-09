#pragma once

// Initialise RTC with a base time. Must be called once before dormant_sleep().
void sleep_manager_init(void);

// Put the Pico into dormant mode for SLEEP_DURATION_SEC seconds.
// Clocks are saved before and restored after wake.
void dormant_sleep(void);
