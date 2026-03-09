# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)

set(PICO_EXTRAS_FETCH_FROM_GIT on)
include(pico_extras_import.cmake)

set(PICO_BOARD pico_w CACHE STRING "Board type")

project(GardenGuard C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(libs/Network-RPI-pico-ESP8285)

