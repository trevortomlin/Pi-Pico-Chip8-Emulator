cmake_minimum_required(VERSION 3.13)

project(test)

include(pico_sdk_import.cmake)

pico_sdk_init()

add_executable(test test.c pico-ssd1306/ssd1306.c)

target_include_directories(test PRIVATE pico-ssd1306/)

pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 1)

pico_add_extra_outputs(test)

target_link_libraries(test pico_stdlib hardware_i2c)
