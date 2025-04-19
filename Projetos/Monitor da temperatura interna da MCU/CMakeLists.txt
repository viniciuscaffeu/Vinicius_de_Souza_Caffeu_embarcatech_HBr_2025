cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Importa SDK
include(pico_sdk_import.cmake)

project(temperatura_mcu C CXX ASM)

pico_sdk_init()

add_executable(temperatura_mcu
    temperatura_mcu.c
    inc/ssd1306_i2c.c
)

pico_set_program_name(temperatura_mcu "temperatura_mcu")
pico_set_program_version(temperatura_mcu "0.1")

# Ativa USB para printf
pico_enable_stdio_uart(temperatura_mcu 0)
pico_enable_stdio_usb(temperatura_mcu 1)

# Adiciona as bibliotecas necessárias
target_link_libraries(temperatura_mcu
    pico_stdlib
    hardware_adc
    hardware_i2c
)

# Inclui diretório atual (onde está o ssd1306.h, se estiver junto ao .c)
target_include_directories(temperatura_mcu PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

pico_add_extra_outputs(temperatura_mcu)
