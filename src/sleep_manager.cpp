#include "sleep_manager.h"

#include <time.h>

#include "pico/stdlib.h"
#include "pico/sleep.h"
#include "pico/aon_timer.h"

#include "hardware/rosc.h"

#define SLEEP_DURATION_SEC  60 * 5      // 5 minutes

void sleep_manager_init(void) {
    struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
    aon_timer_start(&ts);
}

void dormant_sleep(void) {
    struct timespec now, alarm;
    aon_timer_get_time(&now);

    alarm.tv_sec  = now.tv_sec + SLEEP_DURATION_SEC;
    alarm.tv_nsec = now.tv_nsec;

    sleep_ms(10);   // flush UART before clocks stop

    sleep_run_from_xosc();
    sleep_goto_dormant_until(&alarm, NULL);

    // execution resumes here after wake
    sleep_power_up();
}
