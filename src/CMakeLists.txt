# Static library — shared between firmware and tests
add_library(math_utils STATIC
    math_utils.cpp
)

target_include_directories( math_utils PUBLIC 
                            ${CMAKE_SOURCE_DIR}/include
)


add_library(network STATIC
    network/ESP8285.cpp
    network/MQTT.cpp
)


target_include_directories( network PUBLIC 
                            ${CMAKE_SOURCE_DIR}/include/network
                            
)

target_link_libraries(network
    pico_stdlib
    hardware_uart
)


# ────── Firmware target ──────
add_executable( ${PROJECT_NAME} 
                 main.cpp

)

# target_include_directories( ${PROJECT_NAME} PRIVATE 
#                             ${CMAKE_SOURCE_DIR}/include
# )

target_link_libraries(${PROJECT_NAME}
    math_utils
    network
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME}) 