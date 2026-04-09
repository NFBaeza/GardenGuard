# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)

set(PICO_EXTRAS_FETCH_FROM_GIT on)
include(pico_extras_import.cmake)

# Select target board:
#   cmake -DPICO_BOARD=pico_w   ..   → Raspberry Pi Pico W   (RP2040 + ESP8285, default)
#   cmake -DPICO_BOARD=pico2_w  ..   → Raspberry Pi Pico 2 W (RP2350 + CYW43 onboard WiFi)
set(PICO_BOARD pico_w CACHE STRING "Board type: pico_w (RP2040) or pico2_w (RP2350)")

project(GardenGuard C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(src)
if(NOT PICO_BOARD STREQUAL "pico2_w")
    add_subdirectory(libs/Network-RPI-pico-ESP8285)
endif()

