# ────── Firmware target ──────
add_executable( ${PROJECT_NAME} 
                 main.cpp
                 ${CMAKE_SOURCE_DIR}/include

)
target_link_libraries(${PROJECT_NAME}
    math_utils
    network_rpi_pico_esp8285
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME}) 


# Static library — shared between firmware and tests
add_library(math_utils STATIC
    math_utils.cpp
)

target_include_directories(math_utils PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
