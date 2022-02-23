cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_fun C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include_directories(
    include
)

add_executable(pico_fun
    source/fun_main.c
    source/fun_button.c
    source/fun_led.c
    source/fun_timer.c
    source/fun_oled.c
)

pico_enable_stdio_usb(pico_fun 1)

pico_add_extra_outputs(pico_fun)

target_link_libraries(pico_fun 
    pico_stdlib 
    pico_unique_id 
    hardware_rtc 
    hardware_i2c)

