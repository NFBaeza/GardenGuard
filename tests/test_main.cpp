// tests/test_main.cpp
// This file owns the doctest implementation + the main() for Pico

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#ifdef PICO_BUILD
#include "pico/stdlib.h"

int main(int argc, char** argv) {
    stdio_init_all();
    sleep_ms(2000);         // Give USB-CDC time to connect

    doctest::Context ctx;
    ctx.setOption("no-colors", true);   // cleaner on serial output
    ctx.applyCommandLine(argc, argv);

    int res = ctx.run();
    
    // Blink LED to signal test result (pass=slow, fail=fast)
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(res == 0 ? 1000 : 100);
        gpio_put(LED_PIN, 0);
        sleep_ms(res == 0 ? 1000 : 100);
    }
}

#else

int main(int argc, char** argv) {
    doctest::Context ctx;
    ctx.applyCommandLine(argc, argv);
    return ctx.run();
}

#endif