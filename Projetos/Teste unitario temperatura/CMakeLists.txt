cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(adc_temp_project C CXX ASM)
set(CMAKE_C_STANDARD 11)

pico_sdk_init()

add_subdirectory(src)
add_subdirectory(test)
