# ────── Board-specific source selection ──────
# Build with -DPICO_BOARD=pico2_w  → Raspberry Pi Pico 2 W (RP2350 + CYW43, onboard WiFi)
# Build with -DPICO_BOARD=pico_w   → Raspberry Pi Pico W  (RP2040 + ESP8285, default)
if(PICO_BOARD STREQUAL "pico2_w")
    set(MAIN_SRC main_pico2.cpp)
    set(BOARD_SLEEP_LIBS hardware_powman)
    set(BOARD_WIFI_LIBS
        pico_cyw43_arch_lwip_poll
        pico_lwip_mqtt
    )
    set(BOARD_EXTRA_SRCS ${CMAKE_SOURCE_DIR}/libs/mqtt/mqtt.cpp)
    set(BOARD_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libs/mqtt)
else()
    set(MAIN_SRC main.cpp)
    set(BOARD_SLEEP_LIBS hardware_rtc)
    set(BOARD_WIFI_LIBS network_rpi_pico_esp8285)
    set(BOARD_EXTRA_SRCS "")
    set(BOARD_INCLUDE_DIRS "")
endif()

# ────── Firmware target ──────
add_executable( ${PROJECT_NAME}
                 ${MAIN_SRC}
                 sleep_manager.cpp
                 ${BOARD_EXTRA_SRCS}
)
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_adc
    ${BOARD_WIFI_LIBS}
    ${BOARD_SLEEP_LIBS}
    hardware_sleep
    hardware_clocks
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${BOARD_INCLUDE_DIRS}
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME})

