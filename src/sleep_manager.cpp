#include "sleep_manager.h"

#include <time.h>

#include "pico/stdlib.h"
#include "pico/sleep.h"
#include "hardware/clocks.h"
#include "hardware/structs/scb.h"
#include "hardware/structs/clocks.h"
#include "pico/runtime_init.h"
#include "pico/aon_timer.h"
#include "hardware/gpio.h"

#if defined(PICO_RP2350)
#include "hardware/powman.h"
#else
#include "hardware/rosc.h"
#endif

// ── Shared wake callbacks ─────────────────────────────────────────────────────

static void on_wake(uint alarm_num) {}
static void on_aon_wake(void) {}

// ── Clock save/restore ────────────────────────────────────────────────────────

static uint32_t scb_orig;
static uint32_t clock0_orig;
static uint32_t clock1_orig;

static void save_clocks(void) {
    scb_orig    = scb_hw->scr;
    clock0_orig = clocks_hw->sleep_en0;
    clock1_orig = clocks_hw->sleep_en1;
}

static void restore_clocks(void) {
    scb_hw->scr          = scb_orig;
    clocks_hw->sleep_en0 = clock0_orig;
    clocks_hw->sleep_en1 = clock1_orig;
    // Bring PLLs / XOSC / system clocks back to their default running state.
    runtime_init_clocks();
}

// ── dormant_sleep ─────────────────────────────────────────────────────────────

void dormant_sleep(uint32_t duration_ms) {
    save_clocks();
#if defined(PICO_RP2350)
    sleep_goto_sleep_for(duration_ms, on_wake);
#else
    sleep_run_from_xosc();
    sleep_goto_sleep_for(duration_ms, on_wake);
#endif

    sleep_power_up();
    restore_clocks();
    stdio_init_all();
}

// ── deep_sleep (RP2350 only) ──────────────────────────────────────────────────

#if defined(PICO_RP2350)
void deep_sleep(uint32_t duration_ms) {
    powman_timer_set_1khz_tick_source_lposc();
    aon_timer_start_with_timeofday();

    struct timespec now;
    aon_timer_get_time(&now);

    uint64_t wake_ns = (uint64_t)now.tv_sec * 1000000000ull
                     + (uint64_t)now.tv_nsec
                     + (uint64_t)duration_ms * 1000000ull;

    struct timespec ts = {
        .tv_sec  = (time_t)(wake_ns / 1000000000ull),
        .tv_nsec = (long)(wake_ns % 1000000000ull),
    };

    save_clocks();

    sleep_run_from_dormant_source(DORMANT_SOURCE_LPOSC);
    sleep_goto_dormant_until(&ts, on_aon_wake);

    sleep_power_up();

    restore_clocks(); 
    stdio_init_all();
}
#endif
