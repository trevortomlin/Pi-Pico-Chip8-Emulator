cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc)

include(pico_sdk_import.cmake)

project(test C CXX ASM)

pico_sdk_init()

add_executable(test test.c pico-ssd1306/ssd1306.c)

target_include_directories(test PRIVATE pico-ssd1306/)

pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 1)

pico_add_extra_outputs(test)

target_link_libraries(test pico_stdlib hardware_i2c)
