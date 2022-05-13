cmake_minimum_required(VERSION 3.13)

file( GLOB C_SOURCES src/*.c )
#file( GLOB C_HEADERS RELATIVE include/*.h)

#file( GLOB FILES *.c *.h )

set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc)

include(pico_sdk_import.cmake)

project(c8-emulator C CXX ASM)



#add_library(c8-emulator)

#target_link_libraries(c8-emulator ${FILES})

#add_library( c8 ${C_SOURCES} ${C_HEADERS} )

#add_subdirectory( c8 )

pico_sdk_init()

#add_executable(c8-emulator src/main.c src/chip8.c  pico-ssd1306/ssd1306.c)

add_executable(c8-emulator pico-ssd1306/ssd1306.c)

foreach( sf ${C_SOURCES} )
    
    #string( REPLACE ".c" "" exename ${sf} )
    #add_executable(c8-emulator ${sf})
    #target_link_libraries(c8-emulator c8)
    target_sources(c8-emulator PRIVATE ${sf})

endforeach( sf ${C_SOURCES})

target_include_directories(c8-emulator PRIVATE pico-ssd1306/ include/)

pico_enable_stdio_usb(c8-emulator 1)
pico_enable_stdio_uart(c8-emulator 1)

pico_add_extra_outputs(c8-emulator)

target_link_libraries(c8-emulator pico_stdlib hardware_i2c)
