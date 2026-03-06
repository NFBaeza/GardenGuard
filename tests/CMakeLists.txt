set(SOURCES
    test_main.cpp
    test_math_utils.cpp
)

# Header files
set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/math_utils.h
)

add_executable(test_runner
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(test_runner PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/doctest
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(test_runner PRIVATE
    PICO_BUILD                          # triggers Pico main() in test_main.cpp
    DOCTEST_CONFIG_NO_EXCEPTIONS        # Pico SDK has exceptions disabled
    DOCTEST_CONFIG_NO_POSIX_SIGNALS     # no POSIX signals on bare-metal RP2040
    DOCTEST_CONFIG_NO_MULTITHREADING    # no std::mutex on bare-metal RP2040
)

target_link_libraries(test_runner
    math_utils                      # reuse the same lib as firmware
    pico_stdlib
    hardware_gpio
)

pico_enable_stdio_usb(test_runner 1)
pico_enable_stdio_uart(test_runner 0)
pico_add_extra_outputs(test_runner)  # generates test_runner.uf2