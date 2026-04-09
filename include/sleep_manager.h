#pragma once

#include <stdint.h>

#define SLEEP_DURATION_MS_DEFAULT  (5 * 60 * 1000)  // 5 minutes

// Light sleep: clocks gated, SRAM retained, timer wakes the chip.
// Used on RP2040 (Pico W).
void dormant_sleep(uint32_t duration_ms = SLEEP_DURATION_MS_DEFAULT);

// Deep dormant sleep: all PLLs and XOSC stopped, only LPOSC (~32 kHz) runs.
// Lowest power state — wakes after duration_ms via AON timer.
// RP2350 (Pico 2 W) only.
#if defined(PICO_RP2350)
void deep_sleep(uint32_t duration_ms = SLEEP_DURATION_MS_DEFAULT);
#endif
